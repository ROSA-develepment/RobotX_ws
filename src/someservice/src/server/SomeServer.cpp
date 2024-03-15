
#include "SomeServer.h"


SomeServer::SomeServer(Node *parent, std::string const &service)
    : Service(parent, service)
{

}

void SomeServer::processRequest(interfaces::srv::SomeService::Request::SharedPtr request
                                , interfaces::srv::SomeService::Response::SharedPtr response)
{
    RCLCPP_INFO(getLogger(),
                "message: \"%s\" reference: %li",
                request->message.message.c_str(),
                request->message.reference);

    response->answer = "Received " + std::to_string(request->message.reference);
}
