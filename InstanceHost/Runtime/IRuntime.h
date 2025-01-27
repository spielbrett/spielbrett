#pragma once

#include "IObject.h"
#include "../Object.h"

namespace Spielbrett::Runtime {

class IRuntime {
public:
    virtual ~IRuntime() = default;

    virtual std::unique_ptr<IObject> createObjectAndLink(const std::string &objectName, const Object &linkedObject) = 0;
};

}
