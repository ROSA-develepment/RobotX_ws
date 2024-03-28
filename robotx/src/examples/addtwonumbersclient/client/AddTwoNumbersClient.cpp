
#include "AddTwoNumbersClient.h"


AddTwoNumbersClient::AddTwoNumbersClient(Node *parent, std::string const &serviceName)
    : Client(parent, serviceName)
{

}

void AddTwoNumbersClient::setRequest(int first, int second)
{
    _request->first = first;
    _request->second = second;
}

void AddTwoNumbersClient::sendRequest()
{
    waitForServer(std::chrono::seconds(1), "Waiting for add_two_numbers server");

    try
    {
        asyncSendRequest();
        RCLCPP_INFO(getLogger(), "%li", _response->answer);
    }
    catch (std::exception const& e)
    {
        RCLCPP_ERROR(getLogger(), "Service call failed");
    }
}
