#ifndef GRPC_SERVER_H
#define GRPC_SERVER_H

#include "InstanceHost.h"

#include <proto/instance_host.grpc.pb.h>

#include <memory>

class GRPCServer : public instance_host::InstanceHostService::Service
{
public:
    GRPCServer() = delete;
    GRPCServer(InstanceHost &instanceHost);

    void run(const std::string &listenAddr);

    grpc::Status CreateInstance(
        grpc::ServerContext* context,
        const instance_host::CreateInstanceRequest* request,
        instance_host::CreateInstanceResponse* response) override;
    grpc::Status TriggerEvent(
        grpc::ServerContext* context,
        const instance_host::TriggerEventRequest* request,
        instance_host::TriggerEventResponse* response) override;

private:
    InstanceHost &instanceHost;
};

#endif // GRPC_SERVER_H
