
#ifndef ROS_SOMECLIENT_H
#define ROS_SOMECLIENT_H

#include "interfaces/srv/some_service.hpp"
#include "interfaces/msg/some_message.hpp"

#include "rosa/client/Client.h"


class SomeClient : public Client<interfaces::srv::SomeService>
{
public:
    SomeClient(Node* parent, std::string const& serviceName);

    void setRequest(interfaces::msg::SomeMessage const& someMessage);

private:
    void sendRequest() override;
};


#endif //ROS_SOMECLIENT_H
