#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
using namespace cv;
#include "ImgProcessor.h"

namespace whu {
namespace ardrone {
	class ARDroneTracker :public ImgProcessor{
	private:
		vector<KeyPoint> keypoints;
	// set as public  for easy usage
	public:
		ARDroneTracker();
		~ARDroneTracker();
		SimpleBlobDetector* blobDetector;
		SimpleBlobDetector::Params params;
		Point2f center;
		void process(cv::Mat& input, cv::Mat& output);
	};
}
}