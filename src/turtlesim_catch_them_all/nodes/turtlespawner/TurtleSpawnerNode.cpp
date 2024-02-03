
#include "TurtleSpawnerNode.h"


TurtleSpawnerNode::TurtleSpawnerNode()
    : rclcpp::Node("turtle_spawner")
    , _catchTurtleService(this, "catch_turtle", &_turtles)
    , _spawnTurtleClient(this, "spawn")
    , _turtleArrayPublisher(this)
    , _turtleName("turtle")
    , _turtleCounter(2)
{
    declare_parameter("spawn_frequency", 1);
    auto spawnFrequency = get_parameter("spawn_frequency").as_int();

    _turtleArrayPublisher.publishOn("alive_turtles");
    _timer.createWallTimer(this, std::chrono::seconds(spawnFrequency), &TurtleSpawnerNode::generateTurtle);
}

void TurtleSpawnerNode::generateTurtle()
{
    Turtle turtleToSpawn;

    turtleToSpawn.name = _turtleName + std::to_string(_turtleCounter++);
    turtleToSpawn.x = std::rand() % 10;
    turtleToSpawn.y = std::rand() % 10;
    turtleToSpawn.theta = std::rand() % 360;

    _spawnTurtleClient.setRequest(turtleToSpawn);
    _spawnTurtleClient.startWorkerThread();
    _turtles.turtles_array.push_back(turtleToSpawn);
    _turtleArrayPublisher.send(_turtles);
}
