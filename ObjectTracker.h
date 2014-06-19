#ifndef _TK_OBJECT_TRACKER_H_
#define _TK_OBJECT_TRACKER_H_

#pragma once

#include "VideoProcessor.h"
#include "kvpair.h"
#include <functional>

class ObjectTracker :public FrameProcessor {
	cv::Mat gray; // 当前灰度图片
	cv::Mat gray_prev; // 之前的灰度图片
	std::vector<cv::Point2f> points[2];
	std::vector<cv::Point2f> initial; // 追踪点的起始坐标
	std::vector<cv::Point2f> features; // 检测特征
	int max_count; // 最大检测特征
	double qlevel; // 特征质量
	double minDist; // 两个点之间的最小距离
	std::vector<uchar> status; // 追踪点的状态
	std::vector<float> err; // 错误
	cv::Point2f center_pt;
public:
	ObjectTracker() :max_count(500), qlevel(0.05), minDist(10.0) {}
	void process(cv::Mat& frame, cv::Mat& output) {
		//cv::GaussianBlur(frame, frame, cv::Size(3, 3),2.0);
		cv::cvtColor(frame, gray, CV_BGR2GRAY); // 灰度变换
		frame.copyTo(output);
		// 1. 加入新的特征点
		if (addNewPoints()) {
			detectFeaturesPoints();
			points[0].insert(points[0].end(), features.begin(), features.end()); // 加入特征点
			initial.insert(initial.end(), features.begin(), features.end());
		}


		// 对于视频序列的第一帧
		if (gray_prev.empty()) {
			gray.copyTo(gray_prev);
		}
		// 2. 追踪
		// Calculates an optical flow for a sparse feature set using the iterative Lucas-Kanade method with pyramids.
		cv::calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
		// 拒绝一些点
		int k = 0;
		for (int i = 0; i < points[1].size(); i++) {
			if (acceptTrackedPoint(i)) {
				initial[k] = initial[i];
				points[1][k++] = points[1][i];
			}
		}
		points[1].resize(k);
		initial.resize(k);
		// 去除杂点
		RmNoise(points[1], 1200, 4);
		// 3. 处理接受的数据
		handleTrackedPoints(frame, output);
		// 4. 时间推移
		std::swap(points[1], points[0]);
		cv::swap(gray_prev, gray);
	}
	// 检测是否有新的点加入
	bool addNewPoints() {
		return points[0].size() <= 10;
	}
	void detectFeaturesPoints() {
		cv::goodFeaturesToTrack(gray, features, max_count, qlevel, minDist); // 跟踪特征
	}
	bool acceptTrackedPoint(int i) {
		return status[i] &&
			(abs(points[0][i].x - points[1][i].x) + abs(points[0][i].y - points[1][i].y)) > 2;
	}
	void handleTrackedPoints(cv::Mat& frame, cv::Mat& output) {
		cv::Point2f center = CenterPoint(points[1]);
		cv::circle(output, center, 3, cv::Scalar(0, 255, 0), -1);
		//for (int i = 0; i < points[1].size(); i++) {
		//cv::line(output, initial[i], points[1][i], cv::Scalar(255, 255, 255));
		//cv::circle(output, points[1][i], 3, cv::Scalar(255, 255, 255), -1);
		//}
	}
	void RmNoise(std::vector<cv::Point2f>& fp, double H, int N) {
		double dst;
		std::vector<std::vector<tk::kvpair<cv::Point2f, double>>> dst_tbl; // 距离矩阵
		// 计算距离矩阵
		for (size_t i = 0; i < fp.size(); i++) {
			dst_tbl.push_back(std::vector<tk::kvpair<cv::Point2f, double>>());
			for (size_t j = 0; j < fp.size(); j++) {
				dst = std::pow(fp[i].x - fp[j].x, 2.0) + std::pow(fp[i].y - fp[j].y, 2.0);
				//std::cout << "dist" << dst << std::endl;
				dst_tbl[i].push_back(tk::kvpair<cv::Point2f, double>(fp[j], dst));
			}
		}

		// 距离矩阵排序
		for (size_t i = 0; i < dst_tbl.size(); i++) {
			std::sort(dst_tbl[i].begin(), dst_tbl[i].end(), std::greater<tk::kvpair<cv::Point2f, double>>()); // 降序
			size_t k = dst_tbl[i].size();
			for (size_t j = k - 1; k > 0; j--, k--) {
				//std::cout<<"k:" << k << ",j:" << j << std::endl;
				if (dst_tbl[i][j].value>H) {
					dst_tbl[i].resize(dst_tbl[i].size() - 1); // 去掉最后一个
				}
			}
		}

		// 于是每个点得到了近邻点,接下来去掉那些近邻点小于N个的点
		std::vector<std::vector<tk::kvpair<cv::Point2f, double>>>::iterator it = dst_tbl.begin();
		std::vector<cv::Point2f>::iterator it_fp = fp.begin();
		while (it != dst_tbl.end()) {
			if ((*it).size()<N) {
				it_fp = fp.erase(it_fp);
				it++;
			} else {
				it++;
				it_fp++;
			}
		}
	}
	cv::Point2f CenterPoint(const std::vector<cv::Point2f> feature_points) {
		cv::Point2f res(.0, .0);
		const int n = feature_points.size();
		for (int i = 0; i < n; i++) {
			res.x += (feature_points[i].x / n);
			res.y += (feature_points[i].y / n);
		}
		center_pt = res;
		return res;
	}
	cv::Point2f get_obj_center() {
		return center_pt;
	}
};

#endif // _TK_OBJECT_TRACKER_H_