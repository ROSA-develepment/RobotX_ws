
#ifndef __COUNTUNTILCLIENT_H__
#define __COUNTUNTILCLIENT_H__

#include "interfaces/action/count_until.hpp"

#include <rosa/actionclient/ActionClient.h>
#include <rosa/node/Node.h>


using CountUntil = interfaces::action::CountUntil;
using CountUntilGoalHandle = rclcpp_action::ClientGoalHandle<CountUntil>;

class CountUntilClient : public ActionClient<CountUntil>
{
public:
    CountUntilClient(Node* parent, std::string const& service);

    void sendGoal(int targetNumber, double period);

private:
    void goalResult(CountUntilGoalHandle::WrappedResult const& result);
};


#endif //__COUNTUNTILCLIENT_H__
