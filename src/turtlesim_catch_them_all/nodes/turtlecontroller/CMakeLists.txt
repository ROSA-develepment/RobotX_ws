
add_subdirectory(client)
add_subdirectory(main)

target_sources(${TURTLE_CONTROLLER_NODE}
    PRIVATE
        TurtleControllerNode.cpp
        TurtleInteractions.cpp
        TurtleMoveCenter.cpp
)
