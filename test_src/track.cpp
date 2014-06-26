#include "../cv_lib.h"
#pragma comment(lib,cvLIB("core"))
#pragma comment(lib,cvLIB("highgui"))
#pragma comment(lib,cvLIB("legacy"))
#pragma comment(lib,cvLIB("imgproc"))
#pragma comment(lib,cvLIB("video"))


#include "../VideoProcessor.h"
#include "../ObjectTracker.h"


int main() {
	VideoProcessor video;
	video.setInput("E:/BigData/1.avi");
	video.setWinName("input", "output");
	video.setDelay(40);
	ObjectTracker tr;
	video.setProcessor(&tr);
	video.run();


	return 0;
}