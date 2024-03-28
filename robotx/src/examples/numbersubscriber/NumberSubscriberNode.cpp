
#include "NumberSubscriberNode.h"


NumberSubscriberNode::NumberSubscriberNode(std::string const &name)
    : Node(name)
    , _subscriber(this)
{
    _subscriber.subscribe("number_topic",
        [this](auto const message)
        {
            messageHandler(message);
        });
    
    RCLCPP_INFO(getLogger(), "Number publisher node is running");
}

void NumberSubscriberNode::messageHandler(SomeNumber::SharedPtr const message)
{
    RCLCPP_INFO(getLogger(), "Number in the message is %li", message->data);
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberSubscriberNode>("number_subscriber_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
