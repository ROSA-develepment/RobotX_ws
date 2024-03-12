
#ifndef ROS_CLOSEDMESSAGELOOPNODE_H
#define ROS_CLOSEDMESSAGELOOPNODE_H

#include "interfaces/msg/some_message.hpp"
#include "rosa/publisher/Publisher.h"
#include "rosa/subscriber/Subscriber.h"
#include "rosa/timer/Timer.h"

#include "rclcpp/rclcpp.hpp"


class ClosedMessageLoopNode : public rclcpp::Node
{
public:
    ClosedMessageLoopNode(std::string name);

    void sendMessage(const std::string& message);

private:
    void messageCallback(interfaces::msg::SomeMessage::SharedPtr const& message);

    std::string _someTopic;

    Publisher<interfaces::msg::SomeMessage> _someMessagePublisher;
    Subscriber<interfaces::msg::SomeMessage> _someMessageSubscriber;
    Timer _someTimer;

    std::string _someMessage;
    int _someMessageReference;
};


#endif //ROS_CLOSEDMESSAGELOOPNODE_H
