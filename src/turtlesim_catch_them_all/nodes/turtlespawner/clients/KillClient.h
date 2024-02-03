
#ifndef ROS_KILLCLIENT_H
#define ROS_KILLCLIENT_H

#include <include/Client.h>

#include "turtlesim/srv/kill.hpp"
#include "rclcpp/rclcpp.hpp"


using Kill = turtlesim::srv::Kill;

class KillClient : public Client<Kill>
{
public:
    KillClient(rclcpp::Node* parent, std::string const& serviceName);

    void setRequest(std::string const& turtleToKill);

private:
    void sendRequest() override;
};


#endif //ROS_KILLCLIENT_H
