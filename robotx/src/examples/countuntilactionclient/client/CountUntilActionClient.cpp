
#include "CountUntilActionClient.h"


CountUntilActionClient::CountUntilActionClient(Node *parent, std::string const &service)
    : ActionClient(parent, service)
{

}

void CountUntilActionClient::setGoal(int targetNumber, double period)
{
    _options.result_callback = [this](auto const& result) { goalResultCallback(result); };
    _goal.target_number = targetNumber;
    _goal.period = period;
}

void CountUntilActionClient::goalResultCallback(CountUntilGoalHandle::WrappedResult const &result)
{
    RCLCPP_INFO(getLogger(), "Result: %ld", result.result->reached_number);
}
