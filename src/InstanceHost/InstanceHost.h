#ifndef INSTANCE_HOST_H
#define INSTANCE_HOST_H

#include "GRPCServer.h"
#include "Instance.h"
#include "WebsocketServer.h"

#include <memory>

class InstanceHost
{
public:
    InstanceHost();

    int run();

private:
    std::shared_ptr<WebsocketServer> websocketServer;
    std::shared_ptr<GRPCServer> grpcServer;

    std::unordered_map<std::string, std::shared_ptr<Instance>> instances;
};

#endif // INSTANCE_HOST_H
