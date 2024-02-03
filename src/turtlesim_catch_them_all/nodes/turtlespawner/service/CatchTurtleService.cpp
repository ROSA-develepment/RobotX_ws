
#include "CatchTurtleService.h"


CatchTurtleService::CatchTurtleService(rclcpp::Node* parent, const std::string& serviceName, TurtleArray* turtles)
    : Service(parent, serviceName)
    , _killTurtle(parent, "kill")
    , _turtles(turtles)
{

}

void CatchTurtleService::processRequest(CatchTurtle::Request::SharedPtr request,
                                        CatchTurtle::Response::SharedPtr response)
{
    _killTurtle.setRequest(request->turtle.name);
    _killTurtle.startWorkerThread();
    response->name = request->turtle.name;

    std::vector<Turtle>::iterator _it;

    for (_it = _turtles->turtles_array.begin(); _it != _turtles->turtles_array.end(); _it++)
    {
        if (response->name == _it->name)
        {
            _turtles->turtles_array.erase(_it);
        }
    }
}
