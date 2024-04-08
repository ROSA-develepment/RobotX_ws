
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "interfaces/action/count_until.hpp"


using CountUntil = interfaces::action::CountUntil;
using CountUntilGoalHandle = rclcpp_action::ClientGoalHandle<CountUntil>;
using namespace std::placeholders;

class CountUntilClientNode : public rclcpp::Node
{
public:
    CountUntilClientNode() : Node("count_until_client")
    {
        _client = rclcpp_action::create_client<CountUntil>(this, "count_until");
    }

    void sendGoal(int targetNumber, double period)
    {
        // Wait for action server
        _client->wait_for_action_server(std::chrono::milliseconds(1000));

        // Add callbacks
        auto options = rclcpp_action::Client<CountUntil>::SendGoalOptions();
        options.result_callback = std::bind(
            &CountUntilClientNode::goalResultCallback, this, _1);
        options.goal_response_callback = std::bind(
            &CountUntilClientNode::goalResponseCallback, this, _1);

        // Create goal
        auto goal = CountUntil::Goal();
        goal.target_number = targetNumber;
        goal.period = period;
        RCLCPP_INFO(get_logger(), "Sending a goal");
        _client->async_send_goal(goal, options);
    }

private:

    // Callback to know if the goal was accepted or rejected
    void goalResponseCallback(CountUntilGoalHandle::SharedPtr const& goalHandle)
    {
        if (!goalHandle)
        {
            RCLCPP_INFO(get_logger(), "Goal got rejected");
        }
        else
        {
            RCLCPP_INFO(get_logger(), "Goal got accepted");
        }
    }

    // Callback to receive the result once the goal is done
    void goalResultCallback(CountUntilGoalHandle::WrappedResult const& result)
    {
        int reachedNumber = result.result->reached_number;
        RCLCPP_INFO(get_logger(), "Result: %d", reachedNumber);
    }

    rclcpp_action::Client<CountUntil>::SharedPtr _client;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CountUntilClientNode>();
    node->sendGoal(6, 0.8);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
