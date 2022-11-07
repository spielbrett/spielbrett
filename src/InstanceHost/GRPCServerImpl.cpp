#include "GRPCServerImpl.h"

#include "GRPCServer.h"

#include <grpc/status.h>
#include <grpcpp/support/status.h>

GRPCServerImpl::GRPCServerImpl(GRPCServer &grpcServer)
    : grpcServer(grpcServer)
{
}

::grpc::Status GRPCServerImpl::CreateInstance(::grpc::ServerContext* context, const ::instance_host::CreateInstanceRequest* request, ::instance_host::CreateInstanceResponse* response)
{
    return ::grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "not implemented yet");
}

::grpc::Status GRPCServerImpl::TriggerEvent(::grpc::ServerContext* context, const ::instance_host::TriggerEventRequest* request, ::instance_host::TriggerEventResponse* response)
{
    return ::grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "not implemented yet");
}
