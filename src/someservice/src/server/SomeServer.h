
#ifndef ROS_SOMESERVER_H
#define ROS_SOMESERVER_H

#include "interfaces/srv/some_service.hpp"

#include "rosa/service/Service.h"
#include "rosa/node/Node.h"


class SomeServer : public Service<interfaces::srv::SomeService>
{
public:
    SomeServer(Node* parent, std::string const& service);

private:
    void processRequest(interfaces::srv::SomeService::Request::SharedPtr request,
                        interfaces::srv::SomeService::Response::SharedPtr response);
};


#endif //ROS_SOMESERVER_H
