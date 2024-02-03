
#include "TurtleMoveCenter.h"

#include <complex>


void TurtleMoveCenter::registerTarget(Turtle const& target)
{
    _target = target;
}

double TurtleMoveCenter::getDistanceToTarget() const
{
    return _distanceToTarget;
}

Twist TurtleMoveCenter::getNextMove(Pose const& currentPosition)
{
    registerCurrentPosition(currentPosition);
    calculateDistanceToTarget(_target );

    double angleDifference = calculateTargetAngleDifference();

    double const angularK = 1.0;
    double angularVelocity = (std::abs(angleDifference) > 0.01) ? angularK * angleDifference : 0.0;

    double const linearK = 0.5;
    double linearVelocity = (std::abs(angleDifference) <= 0.01) ? linearK * _distanceToTarget : 0.0;

    return setMovement(linearVelocity, angularVelocity);
}

void TurtleMoveCenter::registerCurrentPosition(Pose const& currentPosition)
{
    _currentPosition = currentPosition;
}

void TurtleMoveCenter::calculateDistanceToTarget(Turtle const& target)
{
    _distanceToTarget = std::sqrt(std::pow((target.x - _currentPosition.x), 2) + pow((target.y - _currentPosition.y), 2));
}

double TurtleMoveCenter::calculateTargetAngleDifference() const
{
    double angleToGoal = std::atan2(_target.y - _currentPosition.y, _target.x - _currentPosition.x);

    return  angleToGoal - _currentPosition.theta;
}

Twist TurtleMoveCenter::setMovement(double const& linearVelocity, double const& angularVelocity)
{
    Twist movementMessage;
    
    movementMessage.linear.x = linearVelocity;
    movementMessage.angular.z = angularVelocity;

    return movementMessage;
}

Turtle TurtleMoveCenter::getClosestTurtle(TurtleArray const& turtles)
{
    Turtle closestTarget;
    double distance = 15.56;

    for (auto const& turtle : turtles.turtles_array)
    {
        calculateDistanceToTarget(turtle);
        if (_distanceToTarget < distance)
        {
            closestTarget = turtle;
            distance = _distanceToTarget;
        }
    }
    return closestTarget;
}
