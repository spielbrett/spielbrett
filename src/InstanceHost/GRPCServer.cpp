#include "GRPCServer.h"

#include "InstanceHost.h"

#include <grpc++/server_builder.h>
#include <grpcpp/support/status.h>

GRPCServer::GRPCServer(InstanceHost &instanceHost)
    : instanceHost(instanceHost)
{
}

void GRPCServer::run(const std::string &listenAddr)
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort(listenAddr, grpc::InsecureServerCredentials());
    builder.RegisterService(this);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << listenAddr << std::endl;

    server->Wait();
}

grpc::Status GRPCServer::CreateInstance(
    grpc::ServerContext* context,
    const instance_host::CreateInstanceRequest* request,
    instance_host::CreateInstanceResponse* response)
{
    auto instanceId = instanceHost.createInstance(request->instance_type());
    response->set_instance_id(instanceId);
    return grpc::Status::OK;
}

grpc::Status GRPCServer::TriggerEvent(
    grpc::ServerContext* context,
    const instance_host::TriggerEventRequest* request, 
    instance_host::TriggerEventResponse* response)
{
    return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "not implemented yet");
}
