cmake_minimum_required(VERSION 3.8)
project(tests)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosa REQUIRED)
find_package(rclcpp REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
endif()

ament_add_gtest(publisher_test src/PublisherTest.cpp)
ament_target_dependencies(publisher_test
        rosa
        rclcpp
)

target_include_directories(publisher_test PUBLIC
        ${rosa_INCLUDE_DIRS}
)

ament_package()
#target_link_libraries(publisher_test rosa)
