#pragma once

#include "../../Board.h"
#include "../IObject.h"
#include "../IRuntime.h"
#include "ExternalClass.h"

namespace Spielbrett::Runtime::Python {

class Runtime : public IRuntime
{
public:
    Runtime();

    void loadClass(const std::string &objectName, const std::string &moduleName, const std::string &className);

    std::unique_ptr<IObject> createAndLinkObject(const std::string &objectName, Board::Object *boardObject) override;

private:
    std::unordered_map<std::string, std::unique_ptr<ExternalClass>> externalClasses;
};

}