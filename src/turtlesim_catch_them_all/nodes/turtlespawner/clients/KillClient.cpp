

#include "KillClient.h"


KillClient::KillClient(rclcpp::Node *parent, const std::string &serviceName)
    : Client(parent, serviceName)
{

}

void KillClient::setRequest(std::string const & turtleToKill)
{
    _request->name = turtleToKill;
}

void KillClient::sendRequest()
{
    waitForServer(std::chrono::seconds(1), "Waiting for /kill server to be up");

    try
    {
        asyncSendRequest();
        RCLCPP_INFO(getLogger(), "%s was killed", _request->name.c_str());
    }
    catch (std::exception const& exception)
    {
        RCLCPP_ERROR(getLogger(), "Kill service call failed");
    }
}
