#ifndef _TK_VIDEO_PROCESSOR_H_
#define _TK_VIDEO_PROCESSOR_H_
#pragma once

// TODO: !!!!
#include <cxxlib/common/ImgProcessor.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <iostream>
using namespace cv;
using namespace std;

class VideoProcessor {
private:
	string winNameIn;
	string winNameOut;

	cv::VideoCapture capture;

	int inputType;
	int videostatus; // VS

	void(*process)(Mat&,Mat&);
	ImgProcessor* processor;

	int delay;
public:
	VideoProcessor();

	void setWinName(const string, const string);

	bool setInput(const string filename);
	bool setInput(int capid=0);

	void setProcessor(void(*proc)(Mat&, Mat&));
	void setProcessor(ImgProcessor* proc);

	int run();

	void check_status(int status);

	void setDelay(int);

	enum {
		ST_ALL_OK = 0,
		ST_FILE_INPUT = 1,
		ST_CAM_INPUT =2,
		ST_CAPTURE_NOT_OPEN = 3,
		ST_WIN_NAME_NOT_SET = 4,
		ST_PROC_NOT_SET = 5,
		ST_FRAME_EMPTY = 6,
		VS_STOP = 10,
		VS_RUNNING = 11,
		VS_PAUSE = 12
	};
};



#include "VideoProcessor_impl.h"

#endif // _TK_VIDEO_PROCESSOR_H_