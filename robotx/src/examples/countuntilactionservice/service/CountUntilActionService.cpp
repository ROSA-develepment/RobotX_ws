
#include "CountUntilActionService.h"


CountUntilActionService::CountUntilActionService(Node *parent, std::string const& serviceName)
    : ActionServer(parent, serviceName)
{

}

rclcpp_action::GoalResponse CountUntilActionService::goalCallback(rclcpp_action::GoalUUID const& uuig,
    std::shared_ptr<interfaces::action::CountUntil::Goal const> const& goal)
{
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse CountUntilActionService::cancelCallback(
    std::shared_ptr<CountUntilGoalHandle> const& goalHandle)
{
    return rclcpp_action::CancelResponse::ACCEPT;
}

void CountUntilActionService::handleAcceptedCallback(std::shared_ptr<CountUntilGoalHandle> const& goalHandle)
{
    auto result = std::make_shared<CountUntil::Result>();

    result->reached_number = countTo(
        goalHandle->get_goal()->target_number,
        goalHandle->get_goal()->period);

    goalHandle->succeed(result);
}

int CountUntilActionService::countTo(long targetNumber, double period)
{
    auto counter = 0;
    rclcpp::Rate loopRate(1.0 / period);

    while (counter < targetNumber)
    {
        RCLCPP_INFO(getLogger(), "%d", ++counter);
        loopRate.sleep();
    }

    return counter;
}
