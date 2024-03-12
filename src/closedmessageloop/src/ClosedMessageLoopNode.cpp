
#include "ClosedMessageLoopNode.h"


ClosedMessageLoopNode::ClosedMessageLoopNode(std::string name)
    : Node(name)
    , _someTopic("someTopic")
    , _someMessagePublisher(this, _someTopic)
    , _someMessageSubscriber(this)
    , _someMessage("Some message ")
    , _someMessageReference(0)
{
    _someMessageSubscriber.subscribe(_someTopic, [this](auto const& message) { messageCallback(message);});
    _someTimer.createWallTimer(this, std::chrono::milliseconds(500), &ClosedMessageLoopNode::sendMessage, _someMessage);
}

void ClosedMessageLoopNode::sendMessage(std::string const& message)
{
    auto someMessage = interfaces::msg::SomeMessage();
    someMessage.message = message;
    someMessage.reference = _someMessageReference;

    _someMessagePublisher.send(someMessage);
}

void ClosedMessageLoopNode::messageCallback(interfaces::msg::SomeMessage::SharedPtr const& message)
{
    _someMessageReference = message->reference + 1;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ClosedMessageLoopNode>("closed_message_loop");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
