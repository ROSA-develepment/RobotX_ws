
#include "SpawnTurtleClient.h"


SpawnTurtleClient::SpawnTurtleClient(rclcpp::Node *node, const std::string &serviceName)
    : Client(node, serviceName)
{
}

void SpawnTurtleClient::setRequest(Turtle const& turtleToSpawn)
{
    _request->name = turtleToSpawn.name;
    _request->x = turtleToSpawn.x;
    _request->y = turtleToSpawn.y;
    _request->theta = turtleToSpawn.theta;
}

void SpawnTurtleClient::sendRequest()
{
    waitForServer(std::chrono::seconds(1), "Waiting for /spawn server to be up");

    try
    {
        asyncSendRequest();
        RCLCPP_INFO(getLogger(), "%s was spawned at x%f y%f", _response->name.c_str(), _request->x, _request->y);
    }
    catch (std::exception const& exception)
    {
        RCLCPP_ERROR(getLogger(), "Spawning service call failed");
    }
}
