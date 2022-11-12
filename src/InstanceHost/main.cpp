#include "InstanceHost.h"

#include <grpc++/ext/proto_server_reflection_plugin.h>
#include <Python.h>

int main()
{
    // Single Python interpreter per single InstanceHost process
    Py_Initialize();

    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    InstanceHost instanceHost{};
    return instanceHost.run();
    
    return 0;
}
