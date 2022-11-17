#include "InstanceHost.h"

#include <Python.h>
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
    std::signal(SIGINT, handleShutdown);

    // Single Python interpreter per single InstanceHost process
    Py_Initialize();

    // TODO: Enable this only in debug builds when multiple build configurations are supported
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    const char *grpcListenAddr = std::getenv("GRPC_LISTEN_ADDR");
    if (grpcListenAddr == nullptr) {
        std::cerr << "GRPC_LISTEN_ADDR not set" << std::endl;
        return EXIT_FAILURE;
    }

    return instanceHost.run(std::string(grpcListenAddr));
}
