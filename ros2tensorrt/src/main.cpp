#include <rclcpp/rclcpp.hpp>
#include "VideoPublisher.hpp"
#include "ImageProcessor.hpp"

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Starting nodes");

    auto video_publisher_node = std::make_shared<VideoPublisher>();
    auto image_processor_node = std::make_shared<ImageProcessor>();

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "VideoPublisher and ImageProcessor nodes created");

    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(video_publisher_node);
    executor.add_node(image_processor_node);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Nodes added to executor");

    executor.spin();

    rclcpp::shutdown();
    return 0;
}
