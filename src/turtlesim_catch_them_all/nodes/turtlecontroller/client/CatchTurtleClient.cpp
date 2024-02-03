
#include "CatchTurtleClient.h"

#include <utility>


CatchTurtleClient::CatchTurtleClient(rclcpp::Node* node, std::string const& serviceName)
    : Client(node, serviceName)
{

}

void CatchTurtleClient::setRequest(Turtle const& catchedTurtle)
{
    _request->turtle = catchedTurtle;
}

void CatchTurtleClient::sendRequest()
{
    waitForServer(std::chrono::seconds(1), "Waiting for /catch_turtle server to be up");

    try
    {
        asyncSendRequest();
        RCLCPP_INFO(getLogger(), "%s", _response->name.c_str());
    }
    catch (std::exception const& exception)
    {
        RCLCPP_ERROR(getLogger(), "Catch service call failed");
    }
}
