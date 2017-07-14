// web cam pose est: http://dlib.net/webcam_face_pose_ex.cpp.html

#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

// ROS to openCV image_converter
#include "src/image_converter.h"

// Landmark detector
#include "src/landmark_detector.h"

using namespace dlib;
using namespace std;
using namespace cv;
using namespace cv_bridge;
using namespace ros;

//void imgCallback(const sensor_msgs::Image::ConstPtr& msg) {
//    class CvImage {
//    public:
//        std_msgs::Header header;
//        std::string encoding;
//        cv::Mat image;
//    };
//
//    typedef boost::shared_ptr<CvImage> CvImagePtr;
//
//    // creates copy of image data from ROS message
//    // allows modification of CV image
//    CvImagePtr toCvCopy(const sensor_msgs::ImageConstPtr &source,
//                        const std::string &encoding = std::string());
//    CvImagePtr toCvCopy(const sensor_msgs::Image &source,
//                        const std::string &encoding = std::string());
//}

int landmark_detector::main(int argc, char** argv) {
    landmark_detector ld(argc, argv);
}