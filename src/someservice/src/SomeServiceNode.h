
#ifndef ROS_SOMESERVICENODE_H
#define ROS_SOMESERVICENODE_H

#include "client/SomeClient.h"
#include "server/SomeServer.h"

#include "interfaces/msg/some_message.hpp"

#include "rosa/node/Node.h"
#include "rosa/timer/Timer.h"


class SomeServiceNode : public Node
{
public:
    SomeServiceNode(std::string const& name);

    void requestService();
private:
    SomeClient _someClient;
    SomeServer _someServer;

    Timer _someTimer;

    std::string _someMessage;
    int _someMessageReference;
};


#endif //ROS_SOMESERVICENODE_H
