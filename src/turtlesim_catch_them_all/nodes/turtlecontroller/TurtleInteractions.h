
#ifndef ROS_TURTLEINTERACTIONS_H
#define ROS_TURTLEINTERACTIONS_H

#include "client/CatchTurtleClient.h"
#include "interfaces/msg/turtle_array.hpp"

#include "rosa/publisher/Publisher.h"
#include "rosa/subscriber/Subscriber.h"

#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <rclcpp/node.hpp>


using TurtleArray = interfaces::msg::TurtleArray;
using Pose = turtlesim::msg::Pose;
using Twist = geometry_msgs::msg::Twist;

class TurtleInteractions
{
public:
    explicit TurtleInteractions(rclcpp::Node* parent);

    void sendMovement(Twist message);
    void sendCatchTurtleRequest(Turtle const& cachedTurtle);

    Pose getPosition();
    TurtleArray getTurtles();

private:
    void callback(Pose::SharedPtr const& message);
    void callback(TurtleArray::SharedPtr const& message);
    void waitForTurtleArray();

    CatchTurtleClient _catchTurtleClient;
    Publisher<Twist> _turtleSimPublisher;
    Subscriber<Pose> _turtleSimSubscriber;
    Subscriber<TurtleArray> _turtleSpawnSubscriber;

    Twist goToTargetMessage;
    Pose _currentPosition;
    TurtleArray _turtles;

    rclcpp::Node::SharedPtr _parent;
};

#endif //ROS_TURTLEINTERACTIONS_H
