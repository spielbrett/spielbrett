#pragma once

#include "Instance.h"
#include "InstanceHost.h"

#include "proto/instance_host/service.grpc.pb.h"

#include <grpc++/server.h>

#include <memory>

namespace Spielbrett {

class GRPCServer final : public spielbrett_api::instance_host::InstanceHostService::Service
{
public:
    explicit GRPCServer(std::shared_ptr<InstanceHost> instanceHost);

    void run(const std::string &listenAddr);
    void join();
    void stop();

    grpc::Status CreateInstance(
        grpc::ServerContext *context,
        const spielbrett_api::instance_host::CreateInstanceRequest *request,
        spielbrett_api::instance_host::CreateInstanceResponse *response) override;
    grpc::Status PerformAction(
        grpc::ServerContext *context,
        const spielbrett_api::instance_host::PerformActionRequest *request,
        spielbrett_api::instance_host::PerformActionResponse *response) override;

private:
    std::shared_ptr<InstanceHost> instanceHost;
    std::unique_ptr<grpc::Server> server;
};

}
