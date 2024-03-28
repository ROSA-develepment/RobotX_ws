
#ifndef ROS_ADDTWONUMBERSCLIENTNODE_H
#define ROS_ADDTWONUMBERSCLIENTNODE_H

#include "client/AddTwoNumbersClient.h"

#include "interfaces/srv/some_service.hpp"
#include "rosa/node/Node.h"


using SomeService =  interfaces::srv::SomeService;

class AddTwoNumbersClientNode : public Node
{
public:
    AddTwoNumbersClientNode(std::string const& name);

private:
    AddTwoNumbersClient _client;
};


#endif //ROS_ADDTWONUMBERSCLIENTNODE_H
