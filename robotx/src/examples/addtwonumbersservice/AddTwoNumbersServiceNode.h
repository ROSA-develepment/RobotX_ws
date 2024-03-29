
#ifndef ROS_ADDTWONUMBERSSERVICENODE_H
#define ROS_ADDTWONUMBERSSERVICENODE_H

#include "service/AddTwoNumbersService.h"

#include "rosa/node/Node.h"


class AddTwoNumbersServiceNode : public Node
{
public:
    AddTwoNumbersServiceNode(std::string const& name);

private:

    AddTwoNumbersService _server;
};


#endif //ROS_ADDTWONUMBERSSERVICENODE_H
