
#ifndef __COUNTUNTILACTIONSERVERNODE_H__
#define __COUNTUNTILACTIONSERVERNODE_H__

#include "service/CountUntilActionService.h"

#include "rosa/node/Node.h"

class CountUntilActionServerNode : public Node
{
public:
  CountUntilActionServerNode(std::string const& name);

private:

    CountUntilActionService _server;
};


#endif //__COUNTUNTILACTIONSERVERNODE_H__
