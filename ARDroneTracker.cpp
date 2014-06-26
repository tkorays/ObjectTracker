#include "ARDroneTracker.h"
using whu::ardrone::ARDroneTracker;

ARDroneTracker::ARDroneTracker() {
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

	blobDetector = new SimpleBlobDetector(params);
	blobDetector->create("blob");
}
ARDroneTracker::~ARDroneTracker() {
	delete blobDetector;
}

void ARDroneTracker::process(cv::Mat& input, cv::Mat& output) {
	cvtColor(input, output, CV_RGB2GRAY);
	blobDetector->detect(output, keypoints);
	for (size_t i = 0; i < keypoints.size(); i++) {
		center = keypoints[i].pt;
		circle(output, keypoints[i].pt, 20, cvScalar(255, 0, 0), 4);
	}
	
}