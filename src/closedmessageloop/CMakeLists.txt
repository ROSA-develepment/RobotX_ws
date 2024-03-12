cmake_minimum_required(VERSION 3.8)
project(closed_message_loop)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosa REQUIRED)

add_executable(${PROJECT_NAME} src/ClosedMessageLoopNode.cpp)
ament_target_dependencies(${PROJECT_NAME} interfaces rclcpp rosa)

install(TARGETS ${PROJECT_NAME}
        DESTINATION lib/${PROJECT_NAME}
)

ament_package()
