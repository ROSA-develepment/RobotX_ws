cmake_minimum_required(VERSION 3.8)
project(tests)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosa REQUIRED)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  set(TESTFILES
      main.cpp
      src/PublisherTest.cpp)

  ament_add_gtest(${PROJECT_NAME} ${TESTFILES})

  ament_target_dependencies(${PROJECT_NAME} rosa)
#  target_link_libraries(${PROJECT_NAME} rosa)

  install(TARGETS
            ${PROJECT_NAME}
            DESTINATION lib/${PROJECT_NAME}/
  )

endif()

ament_package()
