
#include "AddTwoNumbersService.h"


AddTwoNumbersService::AddTwoNumbersService(Node *parent, std::string const& service)
    : Service(parent, service)
{

}

void AddTwoNumbersService::processRequest(SomeService::Request::SharedPtr request,
                                         SomeService::Response::SharedPtr response)
{
    response->answer = request->first + request->second;
}
