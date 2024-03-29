cmake_minimum_required(VERSION 3.8)
project(examples)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(interfaces REQUIRED)
find_package(rosa REQUIRED)

add_executable(number_publisher numberpublisher/NumberPublisherNode.cpp)
ament_target_dependencies(number_publisher interfaces rosa)

add_executable(number_subscriber numbersubscriber/NumberSubscriberNode.cpp)
ament_target_dependencies(number_subscriber interfaces rosa)

add_executable(add_two_numbers_client addtwonumbersclient/AddTwoNumbersClientNode.cpp addtwonumbersclient/client/AddTwoNumbersClient.cpp)
ament_target_dependencies(add_two_numbers_client interfaces rosa)

add_executable(add_two_numbers_server addtwonumbersserver/AddTwoNumbersServiceNode.cpp addtwonumbersserver/service/AddTwoNumbersService.cpp)
ament_target_dependencies(add_two_numbers_server interfaces rosa)

install(
        TARGETS number_publisher
                number_subscriber
                add_two_numbers_client
                add_two_numbers_server
        DESTINATION lib/${PROJECT_NAME}/
)

ament_package()
