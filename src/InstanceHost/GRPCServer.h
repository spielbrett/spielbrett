#ifndef GRPC_SERVER_H
#define GRPC_SERVER_H

#include <grpc++/server.h>
#include <proto/instance_host.grpc.pb.h>

#include <memory>

class InstanceHost;

class GRPCServer : public instance_host::InstanceHostService::Service
{
public:
    GRPCServer(InstanceHost &instanceHost);

    void run(const std::string &listenAddr);
    void stop();

    grpc::Status CreateInstance(
        grpc::ServerContext *context,
        const instance_host::CreateInstanceRequest *request,
        instance_host::CreateInstanceResponse *response) override;
    grpc::Status TriggerEvent(
        grpc::ServerContext *context,
        const instance_host::TriggerEventRequest *request,
        instance_host::TriggerEventResponse *response) override;

private:
    InstanceHost &instanceHost;
    std::unique_ptr<grpc::Server> server;
};

#endif // GRPC_SERVER_H
