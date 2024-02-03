
#include "TurtleControllerNode.h"


TurtleControllerNode::TurtleControllerNode()
    : Node("turtle_controller")
    , _interactions(this)
{
    declare_parameter("catch_order", "spawn");
    auto order = get_parameter("catch_order").as_string();
    defineCatchOrder(order);

    _controlLoopTimer.createWallTimer(this, std::chrono::seconds(1), &TurtleControllerNode::controlLoop);
    setTarget();
}

void TurtleControllerNode::controlLoop()
{
    Pose currentPosition = _interactions.getPosition();
    Twist movementMessage = _moveCenter.getNextMove(currentPosition);

    if (_moveCenter.getDistanceToTarget() <= 0.1)
    {
        _interactions.sendCatchTurtleRequest(_target);
        setTarget();
    }
    else
    {
        _interactions.sendMovement(movementMessage);
    }
}

void TurtleControllerNode::setTarget()
{
    _turtles = _interactions.getTurtles();

    _target = _order == CatchOrder::Closest ? _moveCenter.getClosestTurtle(_turtles) : _turtles.turtles_array[0];

    _moveCenter.registerTarget(_target);
}

void TurtleControllerNode::defineCatchOrder(const std::string &order)
{
    _order = order == "spawn" ? CatchOrder::Spawn : CatchOrder::Closest;
}