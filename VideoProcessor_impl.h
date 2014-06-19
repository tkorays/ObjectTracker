#ifndef _TK_VIDEO_PROCESSOR_IMPL_H_
#define _TK_VIDEO_PROCESSOR_IMPL_H_
#pragma once

#include "VideoProcessor.h"

VideoProcessor::VideoProcessor():delay(0) {
	videostatus = VS_STOP;
}

void VideoProcessor::setWinName(const string instr, const string outstr) {
	winNameIn = instr;
	winNameOut = outstr;
}

bool VideoProcessor::setInput(const string filename) {
	inputType = ST_FILE_INPUT;
	capture.release();
	return capture.open(filename);
}
bool VideoProcessor::setInput(int capid) {
	inputType = ST_CAM_INPUT;
	capture.release();
	return capture.open(capid);
}

void VideoProcessor::setProcessor(void(*proc)(Mat&, Mat&)) {
	processor = nullptr;
	process = proc;
}
void VideoProcessor::setProcessor(ImgProcessor* proc) {
	process = nullptr;
	processor = proc;
}



int VideoProcessor::run() {
	Mat frame, output;
	if (!capture.isOpened()) {
		return ST_CAPTURE_NOT_OPEN;
	}
	if (winNameIn.length()==0 || winNameOut.length()==0) {
		return ST_WIN_NAME_NOT_SET;
	}
	if (process==nullptr && processor==nullptr) {
		return ST_PROC_NOT_SET;
	}

	namedWindow(winNameIn);
	namedWindow(winNameOut);

	videostatus = VS_RUNNING;
	while (videostatus == VS_RUNNING || videostatus == VS_PAUSE) {
		int key = waitKey(delay);
		if (key == 's' || key == 27) {
			videostatus = VS_STOP;
			return ST_ALL_OK;
		}
		if (key == 'p') {
			videostatus = VS_PAUSE;
		}
		if (key == 'r') {
			videostatus = VS_RUNNING;
		}
		if (videostatus==VS_PAUSE) {
			continue;
		}
		
		capture >> frame;
		if (frame.empty()) {
			return ST_FRAME_EMPTY;
		}
		imshow(winNameIn, frame);
		if (process!=nullptr) {
			process(frame, output);
		} else if (processor != nullptr) {
			processor->process(frame, output);
		}
		imshow(winNameOut, output);
	}
	return ST_ALL_OK;
}

void VideoProcessor::check_status(int status) {
	switch (status) {
	case ST_CAPTURE_NOT_OPEN:
		cout << "Capture is not correctly setted or not opened..." << endl;
		exit(0);
		break;
	case ST_WIN_NAME_NOT_SET:
		cout << "Windows Name is not setted..." << endl;
		exit(0);
		break;
	case ST_PROC_NOT_SET:
		cout << "Processor not set..." << endl;
		exit(0);
		break;
	case ST_FRAME_EMPTY:
		cout << "Frame Empty..." << endl;
		exit(0);
	case ST_ALL_OK:
		cout << "ok..." << endl;
		break;
	default:
		cout << "ok..." << endl;
		break;
	}
}

void VideoProcessor::setDelay(int d) {
	delay = d;
}

#endif // _TK_VIDEO_PROCESSOR_IMPL_H_