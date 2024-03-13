
cmake_minimum_required(VERSION 3.8)
project(interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
#        "action/CountUntil.action"
#        "msg/Turtle.msg"
        "msg/SomeMessage.msg"
#        "msg/TurtleArray.msg"
#        "srv/CatchTurtle.srv"
)

ament_export_dependencies(rosidl_default_runtime)

install(DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/msg
        ${CMAKE_CURRENT_SOURCE_DIR}/srv
        ${CMAKE_CURRENT_SOURCE_DIR}/action
        DESTINATION share/${PROJECT_NAME}/
)

ament_package()
