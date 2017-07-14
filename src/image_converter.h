//
// Created by sophianielsen on 7/12/17.
//

#ifndef AVATAR_IMAGE_CONVERTER_H
#define AVATAR_IMAGE_CONVERTER_H

#include "image_converter.h"
#include <ros/ros.h>
// allows subscription to compressed image streams
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

class image_converter {
    ros::NodeHandle n;
    image_transport::ImageTransport it;
    image_transport::Publisher image_pub;
    image_transport::Subscriber image_sub;

public:
    image_converter(int argc, char** argv)
            : it(n)
    {
        // Subscribe to input video feed and publish output video feed
        image_sub = it.subscribe("/camera/image_raw", 1,
                                 &image_converter::imageCb, this);
        image_pub = it.advertise("/image_converter/output_video", 1);
    }

    void imageCb(const sensor_msgs::ImageConstPtr& msg) {
        cv_bridge::CvImagePtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception &e) {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }

        // output video stream
        image_pub.publish(cv_ptr->toImageMsg());
    }
};

static int convert_images(int argc, char** argv) {
    ros::init(argc, argv, "image_converter");
    image_converter ic(argc, argv);
    ros::spin();
    return 0;
}

#endif //AVATAR_IMAGE_CONVERTER_H
