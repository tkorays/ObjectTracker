#include <opencv2/opencv.hpp>
#include <cv_link_all.h>
#include "ColorDetector.h"
#include <iostream>
using namespace std;
using namespace cv;

int main() {
	// input: Mat,n,color,color_deviation,scan_step
	// output: vector<point>,the color center
	Mat img = imread("test.jpg");

	vector<Point> center =  ColorDetector::process(img, 2, Vec3i(237,89,93), 30, 1);

	for (size_t i = 0; i < center.size(); i++) {
		cout << center[i].x << " " << center[i].y << endl;
	}
	namedWindow("img");
	circle(img, cv::Point(center[0]), 10, cv::Scalar(0, 255, 0));

	imshow("img", img);
	waitKey(10000);
	return 0;
}