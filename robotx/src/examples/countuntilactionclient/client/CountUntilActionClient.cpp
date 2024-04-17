
#include "CountUntilActionClient.h"


CountUntilActionClient::CountUntilActionClient(Node *parent, std::string const &service)
    : ActionClient(parent, service)
{
    defineFeedbackCallback();
    _timer.createWallTimer(getParent(), std::chrono::seconds(2),
        [this]()
        {
            RCLCPP_INFO(getLogger(), "stop the goal");
            asyncCancelGoal(_goalHandle);
            //_timer.cancel();
        });
}

void CountUntilActionClient::setGoal(int targetNumber, double period)
{
    _goal.target_number = targetNumber;
    _goal.period = period;
}

void CountUntilActionClient::goalResponseCallback(CountUntilGoalHandle::SharedPtr const& response)
{
    if (!response)
    {
        RCLCPP_INFO(getLogger(), "Goal got rejected");
    }
    else
    {
        _goalHandle = response;
        RCLCPP_INFO(getLogger(), "Goal got accepted");
    }
}

void CountUntilActionClient::goalResultCallback(CountUntilGoalHandle::WrappedResult const &result)
{
    auto status = result.code;

    if (status == rclcpp_action::ResultCode::SUCCEEDED)
    {
        RCLCPP_INFO(getLogger(), "Succeeded");
    }
    else
    {
       if (status == rclcpp_action::ResultCode::ABORTED)
       {
           RCLCPP_ERROR(getLogger(), "Aborted");
       }
       else
       {
           if (status == rclcpp_action::ResultCode::CANCELED)
           {
               RCLCPP_WARN(getLogger(), "Canceled");

           }
       }
    }

    RCLCPP_INFO(getLogger(), "Result: %ld", result.result->reached_number);
}

void CountUntilActionClient::defineFeedbackCallback()
{
    auto feedback = [this](auto const& goalHandle,
        std::shared_ptr<CountUntil::Feedback const> const& message)
    {
        goalHandle.get()->get_goal_stamp().seconds();
        RCLCPP_INFO(getLogger(), "Feedback %li, timestamp = %f", message->current_number
            , goalHandle.get()->get_goal_stamp().seconds());
    };

    setFeedbackCallback<CountUntil::Feedback>(feedback);
}
