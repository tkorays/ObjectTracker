#include "../cv_lib.h"
#include <opencv2/opencv.hpp>
#pragma comment(lib,cvLIB("core"))
#pragma comment(lib,cvLIB("highgui"))
#pragma comment(lib,cvLIB("legacy"))
#pragma comment(lib,cvLIB("imgproc"))
#pragma comment(lib,cvLIB("video"))
#pragma comment(lib,cvLIB("features2d"))

#include "../ObjectTracker.h"
using namespace cv;
int main() {
	VideoCapture cap;
	ObjectTracker tracker;
	cap.open(0);
	if (!cap.isOpened()) {
		printf("open capture error!\n");
		exit(0);
	}
	int key;
	Mat frame,out;
	namedWindow("img");
	cap >> frame;
	while ((key=waitKey(1))!=27) {
		cap >> frame;
		if (frame.empty()) {
			printf("frame is empty.\n");
			exit(0);
		}
		tracker.process(frame, out);
		imshow("img", out);
	}
	return 0;
}