#include "GRPCServer.h"

#include "InstanceHost.h"
#include "proto/instance_host.pb.h"

#include <cstddef>
#include <grpc++/server_builder.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/status.h>
#include <stdexcept>

GRPCServer::GRPCServer(InstanceHost &instanceHost) :
    instanceHost(instanceHost)
{
}

void GRPCServer::run(const std::string &listenAddr)
{
    if (server != nullptr) {
        return;
    }

    grpc::ServerBuilder builder;
    builder.AddListeningPort(listenAddr, grpc::InsecureServerCredentials());
    builder.RegisterService(this);

    server = builder.BuildAndStart();
    std::cout << "Server listening on " << listenAddr << std::endl;

    server->Wait();
}

void GRPCServer::stop()
{
    if (server == nullptr) {
        return;
    }

    server->Shutdown();
    server = nullptr;
}

grpc::Status GRPCServer::CreateInstance(
    grpc::ServerContext *context,
    const instance_host::CreateInstanceRequest *request,
    instance_host::CreateInstanceResponse *response)
{
    std::string instanceId;

    try {
        instanceId = instanceHost.createInstance(request->instance_type());
    }
    catch (std::invalid_argument &e) {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, e.what());
    }
    catch (std::runtime_error &) {
        return grpc::Status(grpc::StatusCode::INTERNAL, "an error occured while creating instance");
    }

    response->set_instance_id(instanceId);
    return grpc::Status::OK;
}

grpc::Status GRPCServer::PerformAction(
    grpc::ServerContext *context,
    const instance_host::PerformActionRequest *request,
    instance_host::PerformActionResponse *response)
{
    auto instance = instanceHost.getInstance(request->instance_id());
    if (instance == nullptr) {
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "instance not found");
    }

    instance->performAction(request->user_id(), request->action_name(), request->payload());
    return grpc::Status::OK;
}
