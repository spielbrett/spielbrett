#include "InstanceHost.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <cstdlib>
#include <future>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>

namespace Spielbrett {

InstanceID InstanceHost::createInstance(
    const std::string &instanceType,
    const std::vector<UserID> &userIds)
{
    std::unique_lock lock(sm);

    auto instanceId = generateInstanceId();
    instances[instanceId] = std::make_shared<Instance>(instanceType, userIds);
    return instanceId;
}

std::shared_ptr<Instance> InstanceHost::getInstance(const InstanceID &instanceId) const noexcept
{
    std::shared_lock lock(sm);

    if (!instances.contains(instanceId)) {
        return nullptr;
    }
    return instances.at(instanceId);
}

InstanceID InstanceHost::generateInstanceId() noexcept
{
    return boost::lexical_cast<InstanceID>(generator());
}

}
