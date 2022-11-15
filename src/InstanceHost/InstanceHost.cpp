#include "InstanceHost.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <cstdlib>
#include <future>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>

InstanceHost::InstanceHost() :
    websocketServer(std::make_unique<WebsocketServer>()),
    grpcServer(std::make_unique<GRPCServer>(*this))
{
}

int InstanceHost::run()
{
    if (grpcServer == nullptr) {
        throw std::runtime_error("gRPC server not instantiated");
    }

    grpcServer->run("0.0.0.0:8000");
    grpcServer->join();

    return EXIT_SUCCESS;
}

void InstanceHost::stop()
{
    if (grpcServer == nullptr) {
        return;
    }

    grpcServer->stop();
    grpcServer->join();
}

std::string InstanceHost::createInstance(
    const std::string &instanceType,
    const std::vector<std::string> &userIds)
{
    std::unique_lock lock(sm);

    auto instanceId = generateInstanceId();
    instances[instanceId] = std::make_shared<Instance>(instanceType, userIds);
    return instanceId;
}

std::shared_ptr<Instance> InstanceHost::getInstance(const std::string &instanceId) const noexcept
{
    std::shared_lock lock(sm);

    if (!instances.contains(instanceId)) {
        return nullptr;
    }
    return instances.at(instanceId);
}

std::string InstanceHost::generateInstanceId() noexcept
{
    return boost::lexical_cast<std::string>(generator());
}
