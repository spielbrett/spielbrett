#ifndef GRPC_SERVER_H
#define GRPC_SERVER_H

#include "GRPCServerImpl.h"

#include <memory>

class InstanceHost;

class GRPCServer
{
public:
    GRPCServer() = delete;
    GRPCServer(InstanceHost &instanceHost);

    void run(const std::string &listenAddr);

private:
    std::shared_ptr<GRPCServerImpl> impl;
    InstanceHost &instanceHost;
};

#endif // GRPC_SERVER_H
