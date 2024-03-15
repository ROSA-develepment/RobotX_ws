
#include "SomeServiceNode.h"


SomeServiceNode::SomeServiceNode(std::string const& name)
    : Node(name)
    , _someClient(this, "some_service")
    , _someServer(this, "some_service")
    , _someMessage("Some message ")
    , _someMessageReference(0)
{
    _someTimer.createWallTimer(this, std::chrono::milliseconds(500), &SomeServiceNode::requestService);
}

void SomeServiceNode::requestService()
{
    auto message = interfaces::msg::SomeMessage();
    message.message = _someMessage;
    message.reference = _someMessageReference++;

    _someClient.setRequest(message);
    _someClient.startWorkerThread();
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SomeServiceNode>("some_service_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
