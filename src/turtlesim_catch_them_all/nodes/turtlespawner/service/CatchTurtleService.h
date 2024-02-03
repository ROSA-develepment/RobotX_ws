
#ifndef ROS_CATCHTURTLESERVICE_H
#define ROS_CATCHTURTLESERVICE_H

#include <include/Service.h>
#include "rclcpp/rclcpp.hpp"
#include "interfaces/srv/catch_turtle.hpp"
#include "../clients/KillClient.h"
#include "interfaces/msg/turtle_array.hpp"
#include "interfaces/msg/turtle.hpp"

using TurtleArray = interfaces::msg::TurtleArray;
using Turtle = interfaces::msg::Turtle;

using CatchTurtle = interfaces::srv::CatchTurtle;

class CatchTurtleService : public Service<CatchTurtle>
{
public:
    CatchTurtleService(rclcpp::Node* parent, std::string const& serviceName, TurtleArray* turtles);

private:
    void processRequest(CatchTurtle::Request::SharedPtr request,
                        CatchTurtle::Response::SharedPtr response) override;

    KillClient _killTurtle;

    TurtleArray* _turtles;
};


#endif //ROS_CATCHTURTLESERVICE_H
