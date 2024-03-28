cmake_minimum_required(VERSION 3.8)
project(tests)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(rosa REQUIRED)

  ament_add_gtest(publisher_tests src/PublisherTest.cpp)

  target_include_directories(publisher_tests PUBLIC ${PROJECT_NAME})
  target_link_libraries(publisher_tests rosa/include)

  ament_target_dependencies(publisher_tests rosa)

  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
