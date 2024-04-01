
#ifndef __COUNTUNTILACTIONSERVICE_H__
#define __COUNTUNTILACTIONSERVICE_H__

#include "rosa/action/ActionServer.h"

#include "interfaces/action/count_until.hpp"


using CountUntil = interfaces::action::CountUntil;
using CountUntilGoalHandle = rclcpp_action::ServerGoalHandle<CountUntil>;

class CountUntilActionService : public ActionServer<CountUntil>
{
public:
    CountUntilActionService(Node* parent, std::string const& serviceName);

private:
    rclcpp_action::GoalResponse goalCallback(rclcpp_action::GoalUUID const& uuig,
        std::shared_ptr<interfaces::action::CountUntil::Goal const> const& goal) override;

    rclcpp_action::CancelResponse cancelCallback(
        std::shared_ptr<CountUntilGoalHandle> const& goalHandle) override;

    void handleAcceptedCallback(
        std::shared_ptr<CountUntilGoalHandle> const& goalHandle) override;

    int countTo(long targetNumber, double period);
};


#endif //__COUNTUNTILACTIONSERVICE_H__
