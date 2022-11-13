#include "InstanceHost.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <future>
#include <memory>

InstanceHost::InstanceHost() :
    websocketServer(std::make_unique<WebsocketServer>()),
    grpcServer(std::make_unique<GRPCServer>(*this))
{
}

void InstanceHost::run()
{
    if (grpcServer != nullptr) {
        grpcServer->run("0.0.0.0:8000");
    }
}

void InstanceHost::stop()
{
    if (grpcServer != nullptr) {
        grpcServer->stop();
    }
}

std::string InstanceHost::createInstance(const std::string &instanceType)
{
    auto instanceId = boost::lexical_cast<std::string>(generator());
    instances[instanceId] = std::make_shared<Instance>(instanceType);
    return instanceId;
}
