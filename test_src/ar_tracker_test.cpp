/**
 * @file ar_tracker_test.cpp
 *
 * @brief ”√”⁄≤‚ ‘ARDroneTracker¿‡
 * @author tkroays
 * @date 2014/6/26
 */

#include "../ARDroneTracker.h"
using whu::ardrone::ARDroneTracker;
#include "../cv_lib.h"
#pragma comment(lib,cvLIB("core"))
#pragma comment(lib,cvLIB("highgui"))
#pragma comment(lib,cvLIB("legacy"))
#pragma comment(lib,cvLIB("imgproc"))
#pragma comment(lib,cvLIB("video"))
#pragma comment(lib,cvLIB("features2d"))

#include "../VideoProcessor.h"

int main(int argc, char* argv[]) {

	VideoProcessor video;
	video.setInput("E:/BigData/1.avi");
	video.setWinName("input", "output");
	video.setDelay(40);
	ARDroneTracker tr;
	video.setProcessor(&tr);
	video.run();

	return 0;
}