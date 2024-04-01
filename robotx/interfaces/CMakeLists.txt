
cmake_minimum_required(VERSION 3.8)
project(interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
        "msg/SomeNumber.msg"
        "srv/SomeService.srv"
        "action/CountUntil.action"
)

ament_export_dependencies(rosidl_default_runtime)

install(DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/msg
        ${CMAKE_CURRENT_SOURCE_DIR}/srv
        DESTINATION share/${PROJECT_NAME}/
)

ament_package()
