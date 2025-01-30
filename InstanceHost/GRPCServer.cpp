#include "GRPCServer.h"

#include <google/protobuf/wrappers.pb.h>
#include <grpc++/server_builder.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/status.h>

#include <stdexcept>

namespace Spielbrett {

GRPCServer::GRPCServer(std::shared_ptr<InstanceHost> instanceHost) :
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
    const spielbrett_api::instance_host::CreateInstanceRequest *request,
    spielbrett_api::instance_host::CreateInstanceResponse *response)
{
    std::vector<UserID> userIds(request->user_ids().begin(), request->user_ids().end());

    InstanceID instanceId;
    std::unordered_map<UserID, std::pair<std::string, std::vector<Board::Action>>> renderResults;
    try {
        instanceId = instanceHost->createInstance(request->instance_type(), userIds);
        auto instance = instanceHost->getInstance(instanceId);
        renderResults = instance->render();
    }
    catch (std::invalid_argument &e) {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, e.what());
    }
    catch (std::exception &e) {
        return grpc::Status(grpc::StatusCode::UNKNOWN, e.what());
    }

    response->set_instance_id(instanceId);
    auto &responseMarkup = *response->mutable_markup();
    auto &responseActions = *response->mutable_actions();
    for (const auto &[k, v] : renderResults) {
        const auto &[markup, actions] = v;
        responseMarkup[k] = markup;
        for (const auto &action : actions) {
            auto *newAction = responseActions[k].mutable_actions()->Add();
            newAction->set_object_id(get<0>(action));
            newAction->set_action(get<1>(action));
            for (const auto &arg : get<2>(action)) {
                newAction->add_args(arg);
            }
        }
    }

    return grpc::Status::OK;
}

grpc::Status GRPCServer::PerformAction(
    grpc::ServerContext *context,
    const spielbrett_api::instance_host::PerformActionRequest *request,
    spielbrett_api::instance_host::PerformActionResponse *response)
{
    auto instance = instanceHost->getInstance(request->instance_id());
    if (instance == nullptr) {
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "instance not found");
    }

    std::unordered_map<UserID, std::pair<std::string, std::vector<Board::Action>>> renderResults;
    try {
        std::vector<std::size_t> args(request->action().args().begin(), request->action().args().end());
        instance->performAction(request->user_id(), {request->action().object_id(), request->action().action(), args});
        renderResults = instance->render();
    }
    catch (std::invalid_argument &e) {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, e.what());
    }
    catch (std::exception &e) {
        return grpc::Status(grpc::StatusCode::UNKNOWN, e.what());
    }

    auto &responseMarkup = *response->mutable_markup();
    auto &responseActions = *response->mutable_actions();
    for (const auto &[k, v] : renderResults) {
        const auto &[markup, actions] = v;
        responseMarkup[k] = markup;
        for (const auto &action : actions) {
            auto *newAction = responseActions[k].mutable_actions()->Add();
            newAction->set_object_id(get<0>(action));
            newAction->set_action(get<1>(action));
            for (const auto &arg : get<2>(action)) {
                newAction->add_args(arg);
            }
        }
    }

    return grpc::Status::OK;
}

}
