
#ifndef ROS_NUMBERSUBSCRIBERNODE_H
#define ROS_NUMBERSUBSCRIBERNODE_H

#include "rosa/node/Node.h"
#include "rosa/subscriber/Subscriber.h"

#include "interfaces/msg/some_number.hpp"


using SomeNumber = interfaces::msg::SomeNumber;

class NumberSubscriberNode : public Node
{
public:
    NumberSubscriberNode(std::string const& name);

private:

    void messageHandler(SomeNumber::SharedPtr const message);

    Subscriber<SomeNumber> _subscriber;
};


#endif //ROS_NUMBERSUBSCRIBERNODE_H
