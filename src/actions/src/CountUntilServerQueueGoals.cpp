
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "interfaces/action/count_until.hpp"

#include <queue>

class CountUntilServerNode : public  rclcpp::Node
{
public:
    CountUntilServerNode() : Node("count_until_server")
    {
        _goalQueueTread = std::thread(&CountUntilServerNode::runGoalQueueTread, this);
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

    ~CountUntilServerNode()
    {
        _goalQueueTread.join();
    }

private:

    rclcpp_action::GoalResponse goalCallback(const rclcpp_action::GoalUUID &uuid, std::shared_ptr<const interfaces::action::CountUntil::Goal> goal)
    {
        RCLCPP_INFO(get_logger(), "Recieved a goal");

        if(goal->target_number <= 0.0)
        {
            RCLCPP_INFO(get_logger(), "Rejecting goal");
            return rclcpp_action::GoalResponse::REJECT;
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
        // pushing goal to queue
        std::lock_guard<std::mutex> lock(_mutex);
        _goalQueue.push(goalHandle);
        RCLCPP_INFO(get_logger(), "Adding goal to queue");
        RCLCPP_INFO(get_logger(), "Queue size: %d", (int)_goalQueue.size());
    }

    void runGoalQueueTread()
    {
        rclcpp::Rate loopRate(1000.0);
        while (rclcpp::ok())
        {
            std::shared_ptr<rclcpp_action::ServerGoalHandle<interfaces::action::CountUntil>> nextGoal;
            {
                std::lock_guard<std::mutex> lock(_mutex);
                if (_goalQueue.size() > 0)
                {
                    nextGoal = _goalQueue.front();
                    _goalQueue.pop();
                }
                if (nextGoal)
                {
                    RCLCPP_INFO(get_logger(), "Execute next goal in queue");
                    executeGoal(nextGoal);
                }
            }
            loopRate.sleep();
        }
    }

    void executeGoal(const std::shared_ptr<rclcpp_action::ServerGoalHandle<interfaces::action::CountUntil>> goalHandle)
    {
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
    std::queue<std::shared_ptr<rclcpp_action::ServerGoalHandle<interfaces::action::CountUntil>>> _goalQueue;

    std::thread _goalQueueTread;
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
