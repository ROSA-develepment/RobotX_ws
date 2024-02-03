
#ifndef ROS_CATCHTURTLECLIENT_H
#define ROS_CATCHTURTLECLIENT_H

#include "interfaces/srv/catch_turtle.hpp"

#include "include/Client.h"


using Turtle = interfaces::msg::Turtle;
using CatchTurtle = interfaces::srv::CatchTurtle;

class CatchTurtleClient : public Client<CatchTurtle>
{
public:
    CatchTurtleClient(rclcpp::Node* parentNode, std::string const& serviceName);

    void setRequest(Turtle const& catchedTurtle);

private:
    void sendRequest() override;
};


#endif //ROS_CATCHTURTLECLIENT_H
