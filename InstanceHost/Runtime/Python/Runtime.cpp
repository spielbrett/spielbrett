#include "Runtime.h"
#include "ExternalClass.h"

#include <stdexcept>

namespace Spielbrett::Runtime::Python {

Runtime::Runtime()
{
}

void Runtime::loadClass(const std::string &objectName, const std::string &moduleName, const std::string &className)
{
    externalClasses.emplace(objectName, std::make_unique<ExternalClass>(moduleName, className));
}

std::unique_ptr<IObject> Runtime::createAndLinkObject(const std::string &objectName, Board::Object *boardObject)
{
    if (!externalClasses.contains(objectName)) {
        std::stringstream ss;
        ss << "unknown object: " << objectName;
        throw std::runtime_error(ss.str());
    }

    return externalClasses.at(objectName)->instantiateAndLink(boardObject);
}

}