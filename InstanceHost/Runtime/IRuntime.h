#pragma once

#include "IObject.h"
#include "../Board.h"

namespace Spielbrett::Runtime {

class IRuntime {
public:
    virtual ~IRuntime() = default;

    virtual std::unique_ptr<IObject> createAndLinkObject(const std::string &objectName, Board::Object *boardObject) = 0;
};

}
