
cmake_minimum_required(VERSION 3.8)
project(turtlesim_catch_them_all)

cmake_policy(SET CMP0076 NEW)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#|-----------------------------------------------------|
#||             *** Dependencies ***                  ||
#|-----------------------------------------------------|

set(DEPENDENCIES
        interfaces
        rosa
        turtlesim
        geometry_msgs
        rclcpp
        ament_cmake
)

foreach (DEPENDENCY ${DEPENDENCIES})
  find_package(${DEPENDENCY} REQUIRED)
endforeach ()

#|-----------------------------------------------------|
#||             *** Executables ***                   ||
#|-----------------------------------------------------|

set(TURTLE_CONTROLLER_NODE turtle_controller_node)
set(TURTLE_SPAWNER_NODE turtle_spawner_node)

set(EXECUTABLES
        ${TURTLE_CONTROLLER_NODE}
        ${TURTLE_SPAWNER_NODE}
)

foreach (EXECUTABLE ${EXECUTABLES})
  add_executable(${EXECUTABLE})
  ament_target_dependencies(${EXECUTABLE} ${DEPENDENCIES})
  install(TARGETS ${EXECUTABLE}
          DESTINATION lib/${PROJECT_NAME}
  )
endforeach ()

add_subdirectory(nodes)

ament_package()
