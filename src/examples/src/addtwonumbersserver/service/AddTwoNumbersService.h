
#ifndef ROS_ADDTWONUMBERSSERVICE_H
#define ROS_ADDTWONUMBERSSERVICE_H

#include "rosa/node/Node.h"
#include "rosa/service/Service.h"

#include "interfaces/srv/some_service.hpp"


using SomeService = interfaces::srv::SomeService;

class AddTwoNumbersService : public Service<SomeService>
{
public:
    AddTwoNumbersService(Node* parent, std::string const& service);

private:
    void processRequest(SomeService::Request::SharedPtr request,
                        SomeService::Response::SharedPtr response) override;
};


#endif //ROS_ADDTWONUMBERSSERVICE_H
