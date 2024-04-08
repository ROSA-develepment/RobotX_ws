
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "interfaces/action/count_until.hpp"


using CountUntil = interfaces::action::CountUntil;
using CountUntilGoalHandle = rclcpp_action::ServerGoalHandle<CountUntil>;
using namespace std::placeholders;

class CountUntilServerNode : public rclcpp::Node
{
public:
    CountUntilServerNode() : Node("count_until_server")
    {
        _server = rclcpp_action::create_server<CountUntil>(
            this,
            "count_until",
            std::bind(&CountUntilServerNode::goalCallback, this, _1, _2),
            std::bind(&CountUntilServerNode::cancelCallback, this, _1),
            std::bind(&CountUntilServerNode::handleAcceptedCallback, this, _1)
        );

        RCLCPP_INFO(get_logger(), "Action server has been started");
    }

private:

    rclcpp_action::GoalResponse goalCallback(rclcpp_action::GoalUUID const& uuig, std::shared_ptr<interfaces::action::CountUntil::Goal const> const& goal)
    {
        RCLCPP_INFO(get_logger(), "Received a goal");

        rclcpp_action::GoalResponse response;
        if (goal->target_number <= 0)
        {
            RCLCPP_INFO(get_logger(), "Rejecting goal");
            response = rclcpp_action::GoalResponse::REJECT;
        }
        else
        {
            RCLCPP_INFO(get_logger(), "Accepting goal");
            response = rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
        }

        return response;
    }

    rclcpp_action::CancelResponse cancelCallback(std::shared_ptr<CountUntilGoalHandle> const goalHandle)
    {
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void handleAcceptedCallback(std::shared_ptr<CountUntilGoalHandle> const goalHandle)
    {
        RCLCPP_INFO(get_logger(), "Executing the goal");
        executeGoal(goalHandle);
    }

    void executeGoal(std::shared_ptr<CountUntilGoalHandle> const goalHandle)
    {
        // Get request from goal
        int targetNumber = goalHandle->get_goal()->target_number;
        double period = goalHandle->get_goal()->period;

        int counter = 0;
        rclcpp::Rate loopRate(1.0 / period);
        for (int i = 0; i < targetNumber; i++)
        {
            counter++;
            RCLCPP_INFO(get_logger(), "%d", counter);
            loopRate.sleep();
        }
        // Set final state and return result
        auto result = std::make_shared<CountUntil::Result>();
        result->reached_number = counter;
        goalHandle->succeed(result);
    }

    rclcpp_action::Server<CountUntil>::SharedPtr _server;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CountUntilServerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
