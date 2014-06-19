#include "../cxxlib/cv_lib.h"
#pragma comment(lib,cvLIB("core"))
#pragma comment(lib,cvLIB("highgui"))
#pragma comment(lib,cvLIB("legacy"))
#pragma comment(lib,cvLIB("imgproc"))
#pragma comment(lib,cvLIB("video"))


#include "../cxxlib/VideoProcessor.h"
#include "../cxxlib/ObjectTracker.h"


int main() {
	VideoProcessor video;
	video.setInput("E:/BigData/1.avi");
	video.displayInput("org");
	video.displayOutput("handle");
	video.setDelay(40);
	ObjectTracker tr;
	video.setFrameProcessor(&tr);
	video.run();

	
	return 0;
}
