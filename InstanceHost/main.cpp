#include "GRPCServer.h"
#include "InstanceHost.h"
#include "WebsocketServer.h"

#include <pybind11/embed.h>

#include <grpc++/ext/proto_server_reflection_plugin.h>

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <thread>

std::unique_ptr<GRPCServer> grpcServer;
std::unique_ptr<WebsocketServer> websocketServer;

void handleShutdown(int signal)
{
    if (grpcServer != nullptr) {
        grpcServer->stop();
    }
    if (websocketServer != nullptr) {
        websocketServer->stop();
    }
}

int main()
{
    std::signal(SIGINT, handleShutdown);

    const char *grpcListenAddr = std::getenv("GRPC_LISTEN_ADDR");
    if (grpcListenAddr == nullptr) {
        std::cerr << "GRPC_LISTEN_ADDR not set" << std::endl;
        return EXIT_FAILURE;
    }
    const char *websocketListenAddr = std::getenv("WEBSOCKET_LISTEN_ADDR");
    if (websocketListenAddr == nullptr) {
        std::cerr << "WEBSOCKET_LISTEN_ADDR not set" << std::endl;
        return EXIT_FAILURE;
    }

    // Single Python interpreter per single InstanceHost process
    pybind11::scoped_interpreter guard{};
    pybind11::gil_scoped_release release{};

    auto instanceHost = std::make_shared<InstanceHost>();

    // TODO: Enable reflection only in debug builds when multiple build configurations are supported
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    grpcServer = std::make_unique<GRPCServer>(instanceHost);
    grpcServer->run(grpcListenAddr);

    websocketServer = std::make_unique<WebsocketServer>(instanceHost);
    websocketServer->run(websocketListenAddr);

    grpcServer->join();
    websocketServer->join();

    return EXIT_SUCCESS;
}
