#ifndef GRPC_SERVER_H
#define GRPC_SERVER_H

#include <grpc++/server.h>
#include <proto/services/instance_host/instance_host.grpc.pb.h>

#include <memory>

class InstanceHost;

class GRPCServer : public spielbrett::services::instance_host::InstanceHostService::Service
{
public:
    GRPCServer(InstanceHost &instanceHost);

    void run(const std::string &listenAddr);
    void join();
    void stop();

    grpc::Status CreateInstance(
        grpc::ServerContext *context,
        const spielbrett::services::instance_host::CreateInstanceRequest *request,
        spielbrett::services::instance_host::CreateInstanceResponse *response) override;
    grpc::Status PerformAction(
        grpc::ServerContext *context,
        const spielbrett::services::instance_host::PerformActionRequest *request,
        spielbrett::services::instance_host::PerformActionResponse *response) override;

private:
    InstanceHost &instanceHost;
    std::unique_ptr<grpc::Server> server;
};

#endif // GRPC_SERVER_H
