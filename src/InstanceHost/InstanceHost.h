#ifndef INSTANCE_HOST_H
#define INSTANCE_HOST_H

#include "Instance.h"

#include <boost/uuid/uuid_generators.hpp>

#include <memory>
#include <shared_mutex>
#include <unordered_map>

class InstanceHost
{
public:
    std::string createInstance(
        const std::string &instanceType,
        const std::vector<std::string> &userIds);
    std::shared_ptr<Instance> getInstance(
        const std::string &instanceId) const noexcept;

private:
    std::unordered_map<std::string, std::shared_ptr<Instance>> instances;

    mutable std::shared_mutex sm;
    mutable boost::uuids::random_generator generator;

    std::string generateInstanceId() const noexcept;
};

#endif // INSTANCE_HOST_H
