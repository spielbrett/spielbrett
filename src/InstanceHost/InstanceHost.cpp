#include "InstanceHost.h"

#include "GRPCServer.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <memory>

InstanceHost::InstanceHost()
{
    websocketServer = std::make_shared<WebsocketServer>();
    grpcServer = std::make_shared<GRPCServer>(*this);
}

int InstanceHost::run()
{
    grpcServer->run("0.0.0.0:8000");
    return 0;
}

std::string InstanceHost::createInstance(const std::string &instanceType)
{
    auto instanceId = boost::lexical_cast<std::string>(generator());
    instances[instanceId] = std::make_shared<Instance>(instanceType);
    return instanceId;
}
