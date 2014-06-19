#ifndef _TK_IMG_PROCESSOR_H_
#define _TK_IMG_PROCESSOR_H_
#pragma once

#include <opencv2/core/core.hpp>

class ImgProcessor {
public:
	virtual void process(cv::Mat& input, cv::Mat& output) = 0;
};


#endif // _TK_IMG_PROCESSOR_H_