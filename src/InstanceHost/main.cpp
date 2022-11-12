#include "InstanceHost.h"

#include <Python.h>
#include <grpc++/ext/proto_server_reflection_plugin.h>

int main()
{
    // Single Python interpreter per single InstanceHost process
    Py_Initialize();

    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    InstanceHost instanceHost{};
    return instanceHost.run();

    return 0;
}
