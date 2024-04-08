
#include "CountUntilActionClientNode.h"


CountUntilActionClientNode::CountUntilActionClientNode(std::string const &name)
    : Node(name)
    , _client(this, "count_until")
{

}

void CountUntilActionClientNode::sendGoal(int targetNumber, double period)
{
    _client.setGoal(targetNumber, period);
    _client.asyncSendGoal();
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CountUntilActionClientNode>("count_until_client");
    node->sendGoal(-6, 0.8);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
