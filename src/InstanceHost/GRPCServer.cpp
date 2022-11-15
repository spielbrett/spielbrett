#include "GRPCServer.h"

#include "InstanceHost.h"
#include "proto/instance_host.pb.h"

#include <cstddef>
#include <google/protobuf/wrappers.pb.h>
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
        throw std::runtime_error("server already launched");
    }

    grpc::ServerBuilder builder;
    builder.AddListeningPort(listenAddr, grpc::InsecureServerCredentials());
    builder.RegisterService(this);

    server = builder.BuildAndStart();
    std::cout << "gRPC server listening on " << listenAddr << std::endl;
}

void GRPCServer::join()
{
    if (server == nullptr) {
        return;
    }

    server->Wait();
}

void GRPCServer::stop()
{
    if (server == nullptr) {
        return;
    }

    server->Shutdown();
    std::cout << "Shutting down the gRPC server..." << std::endl;
}

grpc::Status GRPCServer::CreateInstance(
    grpc::ServerContext *context,
    const instance_host::CreateInstanceRequest *request,
    instance_host::CreateInstanceResponse *response)
{
    std::vector<std::string> userIds(request->user_ids().begin(), request->user_ids().end());

    std::string instanceId;
    try {
        instanceId = instanceHost.createInstance(request->instance_type(), userIds);
    }
    catch (std::invalid_argument &e) {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, e.what());
    }
    catch (std::runtime_error &e) {
        return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
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

    try {
        instance->performAction(request->user_id(), request->action());
    }
    catch (std::invalid_argument &e) {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, e.what());
    }
    catch (std::runtime_error &e) {
        return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    }

    return grpc::Status::OK;
}
