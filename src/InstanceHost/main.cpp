#include "InstanceHost.h"

#include <pybind11/embed.h>

#include <grpc++/ext/proto_server_reflection_plugin.h>

#include <csignal>
#include <cstdlib>
#include <iostream>

InstanceHost instanceHost{};

void handleShutdown(int signal)
{
    instanceHost.stop();
}

int main()
{
    const char *grpcListenAddr = std::getenv("GRPC_LISTEN_ADDR");
    if (grpcListenAddr == nullptr) {
        std::cerr << "GRPC_LISTEN_ADDR not set" << std::endl;
        return EXIT_FAILURE;
    }

    // Single Python interpreter per single InstanceHost process
    pybind11::scoped_interpreter guard{};

    // TODO: Enable this only in debug builds when multiple build configurations are supported
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    std::signal(SIGINT, handleShutdown);
    return instanceHost.run(std::string(grpcListenAddr));
}
