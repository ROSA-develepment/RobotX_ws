
#include "CountUntilActionServerNode.h"


CountUntilActionServerNode::CountUntilActionServerNode(std::string const& name)
    : Node(name)
    , _server(this, "count_until")
{
    RCLCPP_INFO(get_logger(), "Count until action server has been started");
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CountUntilActionServerNode>("count_until_server");
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    executor.spin();
    //rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
