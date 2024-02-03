
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "interfaces/action/count_until.hpp"

class CountUntilClient : public rclcpp::Node
{
public:
    CountUntilClient() : Node("count_until_client")
    {
        _countUntilClient = rclcpp_action::create_client<interfaces::action::CountUntil>(this, "count_until");
    }

    void sendGoal(int targetNumber, float period)
    {
        // wait for the action server
        _countUntilClient->wait_for_action_server();

        // create goal
        auto goal = interfaces::action::CountUntil::Goal();
        goal.target_number = targetNumber;
        goal.period = period;

        // add callbacks
        auto options = rclcpp_action::Client<interfaces::action::CountUntil>::SendGoalOptions();
        options.result_callback = std::bind(&CountUntilClient::goalResultCallback, this, std::placeholders::_1);
        options.goal_response_callback = std::bind(&CountUntilClient::goalResponseCallback, this, std::placeholders::_1);
        options.feedback_callback = std::bind(&CountUntilClient::goalFeedbackCallback, this, std::placeholders::_1, std::placeholders::_2);

        // send goal
        RCLCPP_INFO(get_logger(), "Sending goal");
        _countUntilClient->async_send_goal(goal, options);

        // cancel goal test
//        _timer = create_wall_timer(
//            std::chrono::seconds(2),
//            std::bind(&CountUntilClient::timerCallback, this));
    }
private:

    void timerCallback()
    {
        RCLCPP_INFO(get_logger(), "Goal canceled");
        _countUntilClient->async_cancel_goal(_goalHandle);
        _timer->cancel();
    }

    // callback to receive feedback during goal execution
    void goalFeedbackCallback(rclcpp_action::ClientGoalHandle<interfaces::action::CountUntil>::SharedPtr const& goalHandle,
                              std::shared_ptr<interfaces::action::CountUntil::Feedback const> const& feedback)
    {
        int number = static_cast<int>(feedback->current_number);
        RCLCPP_INFO(get_logger(), "Got feedback: %d", number);
    }

    // callback to accept or reject goal
    void goalResponseCallback(rclcpp_action::ClientGoalHandle<interfaces::action::CountUntil>::SharedPtr const& goalHandle)
    {
        if (!goalHandle)
        {
            RCLCPP_INFO(get_logger(), "Goal got rejected");
        }
        else
        {
            _goalHandle = goalHandle;
            RCLCPP_INFO(get_logger(), "Goal got accepted");
        }
    }

    // callback to recieve the result once the goal is done
    void goalResultCallback(rclcpp_action::ClientGoalHandle<interfaces::action::CountUntil>::WrappedResult const& result)
    {
        auto status = result.code;
        if (status == rclcpp_action::ResultCode::SUCCEEDED)
        {
            RCLCPP_INFO(get_logger(), "Succeed");
        }
        else if (status == rclcpp_action::ResultCode::ABORTED)
        {
            RCLCPP_ERROR(get_logger(), "Aborted");
        }
        else if (status == rclcpp_action::ResultCode::CANCELED)
        {
            RCLCPP_ERROR(get_logger(), "Canceled");
        }
        int reachedNumber = result.result->reached_number;
        RCLCPP_INFO(get_logger(), "Result: %d", reachedNumber);
    }

    rclcpp::TimerBase::SharedPtr _timer;

    rclcpp_action::Client<interfaces::action::CountUntil>::SharedPtr _countUntilClient;
    rclcpp_action::ClientGoalHandle<interfaces::action::CountUntil>::SharedPtr _goalHandle;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CountUntilClient>();
    node->sendGoal(6, 0.8);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
