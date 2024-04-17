
#include "NumberPublisherNode.h"


NumberPublisherNode::NumberPublisherNode(std::string const &name)
    : Node(name)
    , _publisher(this, "number_topic")
{
    _number = 0;
    _publishFrequency = 500;

    _timer.createWallTimer(this,
        std::chrono::milliseconds(_publishFrequency),
        [this]() { numberPublisher(); });

    RCLCPP_INFO(getLogger(), "Number publisher node is running");
}

void NumberPublisherNode::numberPublisher()
{
    auto message = SomeNumber();

    message.data = _number++;
    _publisher.send(message);
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisherNode>("number_publisher_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
