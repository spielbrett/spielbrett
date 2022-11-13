#ifndef INSTANCE_HOST_H
#define INSTANCE_HOST_H

#include "GRPCServer.h"
#include "Instance.h"
#include "WebsocketServer.h"

#include <boost/uuid/uuid_generators.hpp>

#include <memory>
#include <unordered_map>

class InstanceHost
{
public:
    InstanceHost();

    void run();
    void stop();

    std::string createInstance(const std::string &instanceType);
    std::shared_ptr<Instance> getInstance(const std::string &instanceId) const noexcept;

private:
    std::unique_ptr<WebsocketServer> websocketServer;
    std::unique_ptr<GRPCServer> grpcServer;

    std::unordered_map<std::string, std::shared_ptr<Instance>> instances;
    boost::uuids::random_generator generator;
};

#endif // INSTANCE_HOST_H
