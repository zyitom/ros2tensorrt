cmake_minimum_required(VERSION 3.15)
project(ros2tensorrt)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
# 在项目的开始处设置
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# 设置TensorRT和其他依赖的寻找路径

# 启用CUDA语言支持
enable_language(CUDA)

# 查找必要的包
find_package(cv_bridge REQUIRED)
find_package(TensorRT REQUIRED)
find_package(OpenCV 4 REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Ceres 2 REQUIRED)
find_package(fmt REQUIRED)
find_package(rclcpp REQUIRED) # 添加ROS 2 rclcpp库的查找

find_package(sensor_msgs REQUIRED)
find_package(rosidl_default_runtime REQUIRED)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/include)

# 包含目录
include_directories(/opt/ros/humble/include/cv_bridge)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${TensorRT_INCLUDE_DIRS})
include_directories(${CERES_INCLUDE_DIRS})
include_directories(${CUDA_INCLUDE_DIRS})

# 链接目录
link_directories(${CUDA_LIBRARY_DIRS})

# 设置源文件
# 设置源文件
set(SOURCE_FILES 
    src/main.cpp
    src/TRTModule.cpp
    src/VideoPublisher.cpp
    src/ImageProcessor.cpp
    # 确保这里列出了所有.cpp文件
)


# 定义一个可执行文件目标
add_executable(ros2tensorrt ${SOURCE_FILES})

# 链接所需的库

target_link_libraries(ros2tensorrt 
                      ${OpenCV_LIBRARIES}
                      ${TensorRT_LIBS}
                      ${CERES_LIBRARIES}
                      fmt::fmt
                      nvonnxparser
                      cuda
                      rclcpp::rclcpp
                      cv_bridge
                      ${rosidl_default_runtime_LIBRARIES}
                      ${cv_bridge_LIBRARIES}
                      ${sensor_msgs_LIBRARIES})
# 添加编译选项
add_compile_options(-Wall -Wextra -Wpedantic)

# 安装目标
install(TARGETS ros2tensorrt DESTINATION lib/${PROJECT_NAME})

# 若使用ROS 2，您还需要添加以下内容以支持ament编译系统
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

