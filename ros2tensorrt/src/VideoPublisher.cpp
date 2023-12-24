#include "VideoPublisher.hpp"

VideoPublisher::VideoPublisher() : Node("video_publisher") {
    publisher_ = this->create_publisher<sensor_msgs::msg::Image>("raw_video_frames", 10);
    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(33),
        std::bind(&VideoPublisher::timer_callback, this));
    if (!cap_.open("/home/zyi/Desktop/rosyolo/dl_final/test.avi")) {
        RCLCPP_ERROR(this->get_logger(), "Failed to open video file");
    } else {
        RCLCPP_INFO(this->get_logger(), "Video file opened successfully");
    }
}

void VideoPublisher::timer_callback() {
    cv::Mat frame;
    if (cap_.read(frame)) {
        RCLCPP_INFO(this->get_logger(), "Publishing a frame");
        auto message = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
        publisher_->publish(*message);
    } else {
        RCLCPP_ERROR(this->get_logger(), "Failed to read a frame from video");
    }
}

