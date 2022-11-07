#include "InstanceHost.h"

#include <memory>

InstanceHost::InstanceHost()
{
    websocketServer = std::make_shared<WebsocketServer>();
    grpcServer = std::make_shared<GRPCServer>(*this);
}

int InstanceHost::run()
{
    grpcServer->run("0.0.0.0:8000");
    return 0;
}
