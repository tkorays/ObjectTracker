#include "ColorDetector.h"
#include <stdint.h>
using namespace cv;
using namespace std;



vector<Point> ColorDetector::process(cv::Mat& img, int num, cv::Vec3i color, int color_dev, int scan_step) {
	vector<Point> centers;
	// 必须是三通道的
	if (img.channels()!=3 || img.empty() || scan_step==0) {
		return centers;
	}
	vector<cv::Point> points;
	const uchar* img_data = (uchar*)img.data;
	for (int i = 0; i < img.rows*img.cols*3; i+=3) {
		// 选择点，非全部扫描 
		if (((i/3)%img.cols)%scan_step!=0 || ((i/3)%img.rows)%scan_step!=0) {
			continue;
		}
		// 颜色在范围内
		if (img_data[i]<(color[2]+color_dev) && img_data[i]>(color[2]-color_dev) &&\
			img_data[i+1]<(color[1] + color_dev) && img_data[i+1]>(color[1] - color_dev)&&\
			img_data[i + 2]<(color[0] + color_dev) && img_data[i + 2]>(color[0] - color_dev)
			) {
			points.push_back(cv::Point(i / img.cols, i%img.cols));
		}
	}
	// 生成随机中心点

	// 聚类
	cluster(points,centers);
	return centers;
}

void ColorDetector::cluster(const std::vector<cv::Point>& pts, std::vector<cv::Point>& centers) {

	return;
}