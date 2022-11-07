#include "GRPCServer.h"

#include <grpc++/server_builder.h>

GRPCServer::GRPCServer(InstanceHost &instanceHost)
    : instanceHost(instanceHost)
{
    impl = std::make_shared<GRPCServerImpl>(*this);
}

void GRPCServer::run(const std::string &listenAddr)
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort(listenAddr, grpc::InsecureServerCredentials());
    builder.RegisterService(impl.get());

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << listenAddr << std::endl;

    server->Wait();
}
