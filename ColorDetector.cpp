#include "ColorDetector.h"
#include <stdint.h>
#include <map>
#include <algorithm>
#include <functional>
using namespace cv;
using namespace std;
#include <time.h>



vector<Point> ColorDetector::process(cv::Mat& img, int num, cv::Vec3i color, int color_dev, int scan_step) {
	vector<Point> centers;
	// 必须是三通道的
	if (img.channels()!=3 || img.empty() || scan_step==0) {
		return centers;
	}
	vector<cv::Point> points;
	const uchar* img_data = (uchar*)img.data;
	for (int i = 0; i < img.rows*img.cols*3; i+=3) {
		// 选择点，非全部扫描 
		if (((i/3)%img.cols)%scan_step!=0 || ((i/3)%img.rows)%scan_step!=0) {
			continue;
		}
		// 颜色在范围内
		if (img_data[i]<(color[2]+color_dev) && img_data[i]>(color[2]-color_dev) &&\
			img_data[i+1]<(color[1] + color_dev) && img_data[i+1]>(color[1] - color_dev)&&\
			img_data[i + 2]<(color[0] + color_dev) && img_data[i + 2]>(color[0] - color_dev)
			) {
			points.push_back(cv::Point(i / img.cols, i%img.cols));
		}
	}
	// 生成随机中心点
	srand(time(NULL));
	for (int i = 0; i < num; i++) {
		centers.push_back(cv::Point(rand() % img.rows, rand() % img.cols));
	}
	// 聚类
	cluster(points,centers);
	return centers;
}

void ColorDetector::cluster(const std::vector<cv::Point>& pts, std::vector<cv::Point>& centers) {
	int dt = 1;
	// 初始化数据bag
	vector<vector<Point>> pt_bag;
	for (int i = 0; i < centers.size(); i++) {
		pt_bag.push_back(vector<Point>());
	}
	multimap<double,int> dist;
	bool flag=false;
	if (!flag) {
		for (size_t pt_cnt = 0; pt_cnt < pts.size(); pt_cnt++) {
			// 对这个点，就算到中心点距离
			for (size_t center_cnt = 0; center_cnt < centers.size(); center_cnt++) {
				pair<double, int> p(powf(centers[center_cnt].x - pts[pt_cnt].x, 2.0) + powf(centers[center_cnt].y - pts[pt_cnt].y, 2.0), center_cnt);
				dist.insert(p);
				std::sort(dist.begin(), dist.end(), less<pair<double, int>>()); // 距离排序
				int index = (*dist.begin()).second;
				pt_bag[center_cnt].push_back(pts[pt_cnt]); // 该点被加入第center_cnt的bag里面
			}
			dist.clear();
		}
		// update center points
		for (size_t i = 0; i < centers.size(); i++) {
			int x = 0, y = 0;
			for (size_t j = 0; j < pt_bag[i].size(); j++) {
				x += pt_bag[i][j].x;
				y += pt_bag[i][j].y;
			}
			x /= pt_bag[i].size();
			y /= pt_bag[i].size();
			// check
			if (abs(centers[i].x - x) <= 1 && abs(centers[i].y - y)<=1) {
				flag = true;
			} else {
				flag = false;
			}
			centers[i].x = x;
			centers[i].y = y;
		}
		
	}
	
	return;
}