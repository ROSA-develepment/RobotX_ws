
#include "SomeClient.h"


SomeClient::SomeClient(Node *parent, std::string const &serviceName)
    : Client(parent, serviceName)
{

}

void SomeClient::setRequest(interfaces::msg::SomeMessage const &someMessage)
{
    _request->message = someMessage;
}

void SomeClient::sendRequest()
{
    waitForServer(std::chrono::seconds(1), "Waiting for server");

    try
    {
        asyncSendRequest();
        RCLCPP_INFO(getLogger(), "%s", _response->answer.c_str());
    }
    catch (std::exception const& exception)
    {
        RCLCPP_ERROR(getLogger(), "Service call failed");
    }
}
