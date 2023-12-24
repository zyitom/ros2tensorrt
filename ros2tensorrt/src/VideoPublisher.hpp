#ifndef VIDEO_PUBLISHER_HPP
#define VIDEO_PUBLISHER_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

class VideoPublisher : public rclcpp::Node {
public:
    VideoPublisher();

private:
    void timer_callback();

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    cv::VideoCapture cap_;
};

#endif // VIDEO_PUBLISHER_HPP

