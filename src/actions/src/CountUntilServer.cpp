
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "interfaces/action/count_until.hpp"

class CountUntilServerNode : public  rclcpp::Node
{
public:
    CountUntilServerNode() : Node("count_until_server")
    {
        _cb_group = create_callback_group(rclcpp::CallbackGroupType::Reentrant);
        countUntilServer = rclcpp_action::create_server<interfaces::action::CountUntil>(
            this,
            "count_until",
            std::bind(&CountUntilServerNode::goalCallback, this, std::placeholders::_1, std::placeholders::_2),
            std::bind(&CountUntilServerNode::cancelCallback, this, std::placeholders::_1),
            std::bind(&CountUntilServerNode::handleAcceptedCallback, this, std::placeholders::_1),
            rcl_action_server_get_default_options(),
            _cb_group
        );
        RCLCPP_INFO(get_logger(), "server started");
    }

private:

    rclcpp_action::GoalResponse goalCallback(const rclcpp_action::GoalUUID &uuid, std::shared_ptr<const interfaces::action::CountUntil::Goal> goal)
    {
        RCLCPP_INFO(get_logger(), "Recieved a goal");

        // policy: Refuse goal if there is a goal active
//        {
//            std::lock_guard<std::mutex> lock(_mutex);
//            if (_goalHandle)
//            {
//                if (_goalHandle->is_active())
//                {
//                    RCLCPP_INFO(get_logger(), "A goal is still active, reject new goal");
//                    return rclcpp_action::GoalResponse::REJECT;
//                }
//            }
//        }

        if(goal->target_number <= 0.0)
        {
            RCLCPP_INFO(get_logger(), "Rejecting goal");
            return rclcpp_action::GoalResponse::REJECT;
        }

        // policy: preempt existing goal when receiving a new valid goal
        {
            std::lock_guard<std::mutex> lock(_mutex);
            if (_goalHandle)
            {
                if (_goalHandle->is_active())
                {
                    RCLCPP_INFO(get_logger(), "Abort current goal and accept new goal");
                    _preemptedGoalId = _goalHandle->get_goal_id();
                }
            }
        }

        RCLCPP_INFO(get_logger(), "Accepting goal");
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse cancelCallback(std::shared_ptr<rclcpp_action::ServerGoalHandle<interfaces::action::CountUntil>> const goalHandle)
    {
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void handleAcceptedCallback(const std::shared_ptr<rclcpp_action::ServerGoalHandle<interfaces::action::CountUntil>> goalHandle)
    {
        RCLCPP_INFO(get_logger(), "Executing goal");
        executeGoal(goalHandle);
    }

    void executeGoal(const std::shared_ptr<rclcpp_action::ServerGoalHandle<interfaces::action::CountUntil>> goalHandle)
    {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _goalHandle = goalHandle;
        }
//        Get request from goal
        int targetNumber = goalHandle->get_goal()->target_number;
        double period = goalHandle->get_goal()->period;

//        Execute action
        int counter = 0;
        auto result = std::make_shared<interfaces::action::CountUntil::Result>();
        auto feedback = std::make_shared<interfaces::action::CountUntil::Feedback>();
        rclcpp::Rate loopRate(1.0/period);
        for (int i = 0; i < targetNumber; i++)
        {
            // for preempting only
            {
                std::lock_guard<std::mutex> lock(_mutex);
                if (goalHandle->get_goal_id() == _preemptedGoalId)
                {
                    result->reached_number = counter;
                    goalHandle->abort(result);
                    return;
                }
            }
            if (goalHandle->is_canceling())
            {
                result->reached_number = counter;
                goalHandle->canceled(result);
                return;
            }
            counter++;
            RCLCPP_INFO(get_logger(), "%d", counter);
            feedback->current_number = counter;
            goalHandle->publish_feedback(feedback);
            loopRate.sleep();
        }
//        Set final state and return result
        result->reached_number = counter;
        goalHandle->succeed(result);
//        goalHandle->abort(result);
    }

    rclcpp_action::Server<interfaces::action::CountUntil>::SharedPtr countUntilServer;
    rclcpp::CallbackGroup::SharedPtr _cb_group;

    std::mutex _mutex;
    std::shared_ptr<rclcpp_action::ServerGoalHandle<interfaces::action::CountUntil>> _goalHandle;
    rclcpp_action::GoalUUID _preemptedGoalId;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CountUntilServerNode>();
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    executor.spin();
//    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
