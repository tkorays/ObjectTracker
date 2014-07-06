#ifndef _TK_COLORDETECTOR_H_
#define _TK_COLORDETECTOR_H_

#include <opencv2/core/core.hpp>
#include <vector>

class ColorDetector {
private:
	ColorDetector();
	ColorDetector(const ColorDetector&);
	ColorDetector& operator=(const ColorDetector&);
	

public:
	static std::vector<cv::Point> process(cv::Mat& img,int num,cv::Vec3i color,int color_dev,int scan_step=1);
	static void cluster(const std::vector<cv::Point>& pts, std::vector<cv::Point>& centers);
};



#endif // _TK_COLORDETECTOR_H_