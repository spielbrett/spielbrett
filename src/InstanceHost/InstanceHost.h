#ifndef INSTANCE_HOST_H
#define INSTANCE_HOST_H

#include "GRPCServer.h"
#include "Instance.h"
#include "WebsocketServer.h"

#include <boost/uuid/uuid_generators.hpp>

#include <memory>
#include <shared_mutex>
#include <unordered_map>

class InstanceHost
{
public:
    InstanceHost();

    int run();
    void stop();

    std::string createInstance(
        const std::string &instanceType,
        const std::vector<std::string> &userIds);
    std::shared_ptr<Instance> getInstance(
        const std::string &instanceId) const noexcept;

private:
    std::unique_ptr<WebsocketServer> websocketServer;
    std::unique_ptr<GRPCServer> grpcServer;

    std::unordered_map<std::string, std::shared_ptr<Instance>> instances;
    boost::uuids::random_generator generator;

    mutable std::shared_mutex sm;

    std::string generateInstanceId() noexcept;
};

#endif // INSTANCE_HOST_H
