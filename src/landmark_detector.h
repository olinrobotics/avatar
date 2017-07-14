//
// Created by sophianielsen on 7/12/17.
//

// if there's a problem, try to subscribing to image transport instead of ROS

#ifndef AVATAR_LANDMARK_DETECTOR_H
#define AVATAR_LANDMARK_DETECTOR_H

#include <ros/ros.h>
#include <std_msgs/String.h>

#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>

#include <opencv2/imgproc/imgproc.hpp>

#include "image_converter.h"

using namespace std;
using namespace dlib;
using namespace ros;
using namespace cv;
using namespace cv_bridge;

class landmark_detector {

    /* subscribes to usb cam node and publishes landmarks to facial_landmarks node
    // input: argc and argv (for changing ros settings from command line)
    // output: pointer to first element of landmark array */

public:
    landmark_detector(int argc, char** argv)
    {
        ros::init(argc, argv, "facial_landmarks");
        ros::NodeHandle landmark_node;

        // make pubisher to facial_landmarks node
        ros::Publisher facial_landmarks_pub =
                landmark_node.advertise<std_msgs::String>
                        ("/facial_landmarks", 1000);

        // set loop frequency to 10Hz
        ros::Rate loop_rate(10);

        // SUBSCRIBE TO USB CAM NODE
        ros::init(argc, argv, "image_converter");
        ros::NodeHandle image_converter_node;

        // PROCESS OPENCV IMAGE
        image_converter ic(argc, argv);
        convert_images(argc, argv);
        ros::Subscriber image_converter_sub = image_converter_node.subscribe("image_converter",
                                                                             1000, image_converter_callback);

    }

    // PUBLISH TO FACIAL_LANDMARKS NODE
    // initialize facial_landmarks node and node handler

    static void get_landmarks(int argc, char** argv) {

        ros::spin();
    };

    void image_converter_callback(const sensor_msgs::ImageConstPtr& msg) {
        // publishes landmarks from cv image to facial landmarks node

        cv_bridge::CvImagePtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
            cv::Mat cv_image_ = cv_ptr*;

            // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
            // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
            // long as temp is valid.  Also don't do anything to temp that would cause it
            // to reallocate the memory which stores the image as that will make cimg
            // contain dangling pointers.  This basically means you shouldn't modify temp
            // while using cimg.
            cv_image<bgr_pixel> cimg(cv_image_);

            // Detect faces
            std::vector<dlib::rectangle> faces = detector(cimg);
            // Find pose of each face
            std::vector<full_object_detection> shapes;
            for (unsigned long i = 0; i < faces.size(); ++i)
                shapes.push_back(pose_model(cimg, faces[i]));

            facial_landmarks_pub.publish(&shapes);
        }
        catch (cv_bridge::Exception &e) {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }


    };
};


#endif //AVATAR_LANDMARK_DETECTOR_H
