#ifndef INSTANCE_HOST_H
#define INSTANCE_HOST_H

#include "Instance.h"
#include "WebsocketServer.h"

#include <boost/uuid/uuid_generators.hpp>

#include <memory>
#include <unordered_map>

class GRPCServer;

class InstanceHost
{
public:
    InstanceHost();

    int run();

    std::string createInstance(const std::string &instanceType);

private:
    std::shared_ptr<WebsocketServer> websocketServer;
    std::shared_ptr<GRPCServer> grpcServer;

    std::unordered_map<std::string, std::shared_ptr<Instance>> instances;
    boost::uuids::random_generator generator;
};

#endif // INSTANCE_HOST_H
