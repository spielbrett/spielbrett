#include "InstanceHost.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <future>
#include <memory>
#include <mutex>
#include <shared_mutex>

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
    std::unique_lock lock(sm);

    auto instanceId = boost::lexical_cast<std::string>(generator());
    instances[instanceId] = std::make_shared<Instance>(instanceType);
    return instanceId;
}

std::shared_ptr<Instance> InstanceHost::getInstance(const std::string &instanceId) const noexcept
{
    std::shared_lock lock(sm);

    if (instances.count(instanceId) == 0) {
        return nullptr;
    }
    return instances.at(instanceId);
}
