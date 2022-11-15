#include "InstanceHost.h"

#include <Python.h>
#include <grpc++/ext/proto_server_reflection_plugin.h>

#include <csignal>

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

    return instanceHost.run();
}
