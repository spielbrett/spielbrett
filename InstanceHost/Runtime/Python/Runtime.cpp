#include "Runtime.h"

namespace Spielbrett::Runtime::Python {

Runtime::Runtime()
{
}

std::unique_ptr<IObject> Runtime::createObjectAndLink(const std::string &objectName, const Object &linkedObject)
{
    throw std::logic_error("not implemented");
}

}