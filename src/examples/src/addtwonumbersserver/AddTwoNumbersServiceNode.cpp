
#include "AddTwoNumbersServiceNode.h"


AddTwoNumbersServiceNode::AddTwoNumbersServiceNode(std::string const &name)
    : Node(name)
    , _server(this, "add_two_numbers")
{
    RCLCPP_INFO(getLogger(), "Add Two Numbers Service Node is running");
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoNumbersServiceNode>("add_two_numbers_service");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
