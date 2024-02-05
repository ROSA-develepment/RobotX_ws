
#ifndef ROS_TURTLESPAWNERNODE_H
#define ROS_TURTLESPAWNERNODE_H

#include <rosa/publisher/Publisher.h>
#include <rosa/timer/Timer.h>

#include "interfaces/msg/turtle_array.hpp"

#include "rclcpp/rclcpp.hpp"
#include "clients/SpawnTurtleClient.h"
#include "service/CatchTurtleService.h"


using TurtleArray = interfaces::msg::TurtleArray;

class TurtleSpawnerNode : public rclcpp::Node
{
public:
    TurtleSpawnerNode();

    void generateTurtle();

private:
    CatchTurtleService _catchTurtleService;
    SpawnTurtleClient _spawnTurtleClient;
    Publisher<TurtleArray> _turtleArrayPublisher;
    Timer _timer;

    std::thread _threads;

    TurtleArray _turtles;

    std::string _turtleName;
    uint8_t _turtleCounter;
};


#endif //ROS_TURTLESPAWNERNODE_H
