#pragma once

#include "Instance.h"

#include <boost/uuid/uuid_generators.hpp>

#include <memory>
#include <shared_mutex>
#include <unordered_map>

using InstanceID = std::string;

namespace Spielbrett {

class InstanceHost final
{
public:
    InstanceID createInstance(
        const std::string &instanceType,
        const std::vector<UserID> &userIds);
    std::shared_ptr<Instance> getInstance(
        const InstanceID &instanceId) const noexcept;

private:
    InstanceID generateInstanceId() noexcept;

    std::unordered_map<InstanceID, std::shared_ptr<Instance>> instances;

    mutable std::shared_mutex sm;
    boost::uuids::random_generator generator;
};

}
