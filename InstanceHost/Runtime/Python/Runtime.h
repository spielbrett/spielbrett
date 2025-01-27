#pragma once

#include "../IObject.h"
#include "../IRuntime.h"
#include "ExternalClass.h"

namespace Spielbrett::Runtime::Python {

class Runtime : public IRuntime
{
public:
    Runtime();
    std::unique_ptr<IObject> createObjectAndLink(const std::string &objectName, const Object &linkedObject) override;

private:
    std::unordered_map<std::string, ExternalClass> externalClasses;
};

}