
#ifndef __COUNTUNTILACTIONCLIENTNODE_H__
#define __COUNTUNTILACTIONCLIENTNODE_H__

#include "client/CountUntilActionClient.h"

#include <rosa/node/Node.h>


class CountUntilActionClientNode : public Node
{
public:
    CountUntilActionClientNode(std::string const& name);

    void sendGoal(int targetNumber, double period);

private:
    CountUntilActionClient _client;
};

#endif //__COUNTUNTILACTIONCLIENTNODE_H__
