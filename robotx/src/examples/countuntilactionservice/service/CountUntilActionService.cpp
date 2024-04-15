
#include "CountUntilActionService.h"


CountUntilActionService::CountUntilActionService(Node *parent, std::string const& serviceName)
    : ActionServer(parent, serviceName)
{

}

rclcpp_action::GoalResponse CountUntilActionService::goalCallback(rclcpp_action::GoalUUID const& uuig,
    std::shared_ptr<interfaces::action::CountUntil::Goal const> const& goal)
{
    RCLCPP_INFO(getLogger(), "Received a goal");

    rclcpp_action::GoalResponse response;
    if (goal->target_number <= 0)
    {
        RCLCPP_INFO(getLogger(), "Rejecting goal");
        response = rclcpp_action::GoalResponse::REJECT;
    }
    else
    {
        RCLCPP_INFO(getLogger(), "Accepting goal");
        response = rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    return response;
}

rclcpp_action::CancelResponse CountUntilActionService::cancelCallback(
    std::shared_ptr<CountUntilGoalHandle> const& goalHandle)
{
    return rclcpp_action::CancelResponse::ACCEPT;
}

void CountUntilActionService::handleAcceptedCallback(std::shared_ptr<CountUntilGoalHandle> const& goalHandle)
{
    auto result = std::make_shared<CountUntil::Result>();

    auto counter = 0;
    auto feedback = std::make_shared<CountUntil::Feedback>();
    rclcpp::Rate loopRate(1.0 / goalHandle->get_goal()->period);
    while (counter < goalHandle->get_goal()->target_number)
    {
        RCLCPP_INFO(getLogger(), "%d", ++counter);
        feedback->current_number = counter;
        goalHandle->publish_feedback(feedback);
        loopRate.sleep();
    }

    goalHandle->succeed(result);
}
