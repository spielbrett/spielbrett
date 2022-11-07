#ifndef GRPC_SERVER_IMPL_H
#define GRPC_SERVER_IMPL_H

#include <proto/instance_host.grpc.pb.h>

class GRPCServer;

class GRPCServerImpl : public instance_host::InstanceHostService::Service
{
public:
    GRPCServerImpl() = delete;
    GRPCServerImpl(GRPCServer &grpcServer);

    ::grpc::Status CreateInstance(::grpc::ServerContext* context, const ::instance_host::CreateInstanceRequest* request, ::instance_host::CreateInstanceResponse* response) override;
    ::grpc::Status TriggerEvent(::grpc::ServerContext* context, const ::instance_host::TriggerEventRequest* request, ::instance_host::TriggerEventResponse* response) override;

private:
    GRPCServer &grpcServer;
};

#endif // GRPC_SERVER_IMPL_H
