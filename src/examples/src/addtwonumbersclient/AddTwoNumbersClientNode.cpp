
#include "AddTwoNumbersClientNode.h"


AddTwoNumbersClientNode::AddTwoNumbersClientNode(std::string const &name)
    : Node(name)
    , _client(this, "add_two_numbers")
{
    _client.setRequest(21, 21);
    _client.startWorkerThread();

    RCLCPP_INFO(getLogger(), "Add Two Numbers Client Node is running");
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoNumbersClientNode>("add_two_numbers_client");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
