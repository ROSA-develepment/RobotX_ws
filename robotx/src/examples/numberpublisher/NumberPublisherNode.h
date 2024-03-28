
#ifndef ROS_NUMBERPUBLISHERNODE_H
#define ROS_NUMBERPUBLISHERNODE_H

#include "rosa/node/Node.h"
#include "rosa/publisher/Publisher.h"
#include "rosa/timer/Timer.h"

#include "interfaces/msg/some_number.hpp"


using SomeNumber = interfaces::msg::SomeNumber;

class NumberPublisherNode : public Node
{
public:
    NumberPublisherNode(std::string const& name);

private:
    void numberPublisher();

    Publisher<SomeNumber> _publisher;
    Timer _timer;

    int _number;
    int _publishFrequency;
};


#endif //ROS_NUMBERPUBLISHERNODE_H
