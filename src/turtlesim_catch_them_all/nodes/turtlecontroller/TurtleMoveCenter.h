
#ifndef ROS_TURTLEMOVECENTER_H
#define ROS_TURTLEMOVECENTER_H

#include "interfaces/msg/turtle_array.hpp"
#include "interfaces/msg/turtle.hpp"

#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"


using TurtleArray = interfaces::msg::TurtleArray;
using Turtle = interfaces::msg::Turtle;
using Pose = turtlesim::msg::Pose;
using Twist = geometry_msgs::msg::Twist;

class TurtleMoveCenter
{
public:
    void registerTarget(Turtle const& target);
    double getDistanceToTarget() const;
    Turtle getClosestTurtle(TurtleArray const& turtles);

    Twist getNextMove(Pose const& currentPosition);
    void registerCurrentPosition(Pose const& currentPosition);
    void calculateDistanceToTarget(Turtle const& target);
    double calculateTargetAngleDifference() const;
    Twist setMovement(double const& linearVelocity, double const& angularVelocity);

private:
    double _distanceToTarget;
    Pose _currentPosition;
    Turtle _target;
};


#endif //ROS_TURTLEMOVECENTER_H
