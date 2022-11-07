#include "InstanceHost.h"

#include <grpc++/ext/proto_server_reflection_plugin.h>

int main()
{
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    InstanceHost instanceHost{};
    return instanceHost.run();
}
