#include <opencv2/opencv.hpp>
#include <cv_link_all.h>
#include "ColorDetector.h"
#include <iostream>
using namespace std;
using namespace cv;

int main() {
	// input: Mat,n,color,color_deviation,scan_step
	// output: vector<point>,the color center
	
	Mat img = imread("test1.jpg");
	//img.resize(400, 300);
	cv::resize(img, img, cv::Size(400, 300));
	printf("size:(%d,%d)\n", img.cols, img.rows);

	/* 仅仅支持一个点的，所以第二个参数在这里无效，第四个参数为颜色误差，第五个为扫描间隔。 */
	//237,27,36
	vector<Point> center =  ColorDetector::process(img, 1, Vec3i(254,155,0), 20, 3);

	for (size_t i = 0; i < center.size(); i++) {
		cout << center[i].x << " " << center[i].y << endl;
	}
	namedWindow("img");
	circle(img, center[0], 10, cv::Scalar(0, 255, 0),4);
	

	imshow("img", img);
	waitKey(10000);
	
	return 0;
}