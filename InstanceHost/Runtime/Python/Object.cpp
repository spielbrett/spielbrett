#include "Object.h"

namespace Spielbrett::Runtime::Python {

Object::Object()
{
}

Board::Object *Object::getBoardObject() const
{
    return boardObject;
}

void Object::setBoardObject(Board::Object *boardObject)
{
    this->boardObject = boardObject;
}

}
