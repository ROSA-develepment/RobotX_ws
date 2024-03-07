
add_subdirectory(clients)
add_subdirectory(main)
add_subdirectory(service)

target_sources(${TURTLE_SPAWNER_NODE}
    PRIVATE
        TurtleSpawnerNode.cpp
)
