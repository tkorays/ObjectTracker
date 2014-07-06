#include <opencv2/opencv.hpp>
#include <cv_link_all.h>
#include "ColorDetector.h"
using namespace cv;

int main() {
	// input: Mat,n,color,color_deviation,scan_step
	// output: vector<point>,the color center
	Mat img = imread("");

	vector<Point> center =  ColorDetector::process(img, 2, Vec3i(), 10, 1);

	return 0;
}