
#ifndef __COUNTUNTILCLIENT_H__
#define __COUNTUNTILCLIENT_H__

#include "interfaces/action/count_until.hpp"

#include <rosa/actionclient/ActionClient.h>
#include <rosa/node/Node.h>


using CountUntil = interfaces::action::CountUntil;
using CountUntilGoalHandle = rclcpp_action::ClientGoalHandle<CountUntil>;

class CountUntilActionClient : public ActionClient<CountUntil>
{
public:
    CountUntilActionClient(Node* parent, std::string const& service);

    void setGoal(int targetNumber, double period);

private:
    void goalResultCallback(CountUntilGoalHandle::WrappedResult const& result);
};


#endif //__COUNTUNTILCLIENT_H__
