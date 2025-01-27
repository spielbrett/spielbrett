#pragma once

#include "../../Board.h"

#include <memory>

namespace Spielbrett::Runtime::Python
{

class Object
{
public:
    Object();

    Board::Object *getBoardObject() const;
    void setBoardObject(Board::Object *boardObject);

private:
    Board::Object *boardObject;
};

}
