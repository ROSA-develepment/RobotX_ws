cmake_minimum_required(VERSION 3.8)
project(actions)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(interfaces REQUIRED)


add_executable(count_until_server src/CountUntilServerNode.cpp)
ament_target_dependencies(count_until_server rclcpp rclcpp_action interfaces )

add_executable(count_until_client src/CountUntilClientNode.cpp)
ament_target_dependencies(count_until_client rclcpp rclcpp_action interfaces )

ament_package()
