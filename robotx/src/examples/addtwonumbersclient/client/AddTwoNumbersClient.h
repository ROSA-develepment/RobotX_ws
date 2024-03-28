
#ifndef ROS_ADDTWONUMBERSCLIENT_H
#define ROS_ADDTWONUMBERSCLIENT_H

#include "interfaces/srv/some_service.hpp"

#include "rosa/client/Client.h"


using SomeService = interfaces::srv::SomeService;

class AddTwoNumbersClient : public Client<SomeService>
{
public:
    AddTwoNumbersClient(Node* parent, std::string const& serviceName);

    void setRequest(int first, int second);

private:
    void sendRequest() override;

};


#endif //ROS_ADDTWONUMBERSCLIENT_H
