#pragma once

#include "../Board.h"

#include <string>

namespace Spielbrett::Runtime {

class IObject {
public:
    virtual ~IObject() = default;

    virtual void setTemplate(const std::string &templateStr) = 0;
    virtual void performAction(int playerIndex, const Board::Object::Action &action) = 0;
    virtual std::string renderContents(int playerIndex) = 0;
};

}