#include "InstanceHost.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <cstdlib>
#include <future>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>

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

std::string InstanceHost::generateInstanceId() const noexcept
{
    return boost::lexical_cast<std::string>(generator());
}
