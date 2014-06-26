/**
 * @file tracker_1.cpp
 * 
 * @brief 块检测，用于研究
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "../cv_lib.h"
#pragma comment(lib,cvLIB("core"))
#pragma comment(lib,cvLIB("highgui"))
#pragma comment(lib,cvLIB("legacy"))
#pragma comment(lib,cvLIB("imgproc"))
#pragma comment(lib,cvLIB("video"))
#pragma comment(lib,cvLIB("features2d"))
using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	namedWindow("out");
	
	SimpleBlobDetector::Params params;
	params.minThreshold = 40;
	params.maxThreshold = 60;
	params.thresholdStep = 5;
	params.minArea = 50;
	params.minConvexity = 0.4f;
	params.minInertiaRatio = 0.1f;
	params.maxArea = 600;
	params.maxConvexity = 2.0f;
	params.filterByColor = false;
	params.filterByCircularity = false;
	
	SimpleBlobDetector detector(params);
	detector.create("blob");
	vector<KeyPoint> keypoints;
	
	VideoCapture cap;
	cap.open("E:/BigData/1.avi");
	if (!cap.isOpened()) {
		printf("open capture failed...");
		return -1;
	}
	Mat frame;
	Mat gray_frame;
	while (true) {
		if (27 == waitKey(40)) {
			break;
		}
		cap >> frame;
		if (frame.empty()) {
			break;
		}
		cvtColor(frame, gray_frame, CV_RGB2GRAY);
		detector.detect(gray_frame, keypoints);
		for (size_t i = 0; i < keypoints.size(); i++) {
			circle(gray_frame, keypoints[i].pt, 20, cvScalar(255, 0, 0), 4);
			printf("center: (%f,%f).\n", keypoints[i].pt.x, keypoints[i].pt.y);
		}
		imshow("out", gray_frame);
	}


	return 0;
}