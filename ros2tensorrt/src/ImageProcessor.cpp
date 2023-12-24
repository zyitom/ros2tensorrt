#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor() : Node("image_processor") {
    // 确保这里的参数与 TRTModule 的构造函数定义相匹配
    std::string onnx_file_path = "/home/zyi/Desktop/rosyolo/dl_final/src/ros2tensorrt/model-opt-3.onnx";
    std::string cache_file_path = "/home/zyi/Desktop/rosyolo/dl_final/src/ros2tensorrt/model-opt-3.cache";
    trtModule = std::make_unique<TRTModule>(onnx_file_path, cache_file_path);
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
        "raw_video_frames", 10,
        std::bind(&ImageProcessor::image_callback, this, std::placeholders::_1));
    publisher_ = this->create_publisher<sensor_msgs::msg::Image>("processed_video_frames", 10);
}
void ImageProcessor::image_callback(const sensor_msgs::msg::Image::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "Received a frame for processing");
    cv::Mat frame = cv_bridge::toCvCopy(msg, "bgr8")->image;

    // Process frame with TRTModule
    std::vector<bbox_t> boxes = (*trtModule)(frame);

    // Draw bounding boxes on the frame
    for (const auto& box : boxes) {
        for (int i = 0; i < 4; ++i) {
            cv::line(frame, box.pts[i], box.pts[(i + 1) % 4], cv::Scalar(0, 255, 0), 2);
        }
    }

    // Convert the frame with bounding boxes to a ROS message and publish
    auto message = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
    publisher_->publish(*message);
    RCLCPP_INFO(this->get_logger(), "Publishing a processed frame");
    publisher_->publish(*message);
}


