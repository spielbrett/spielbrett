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

std::string Object::getTemplate() const
{
    return templateStr;
}

void Object::setTemplate(const std::string &templateStr)
{
    this->templateStr = templateStr;
}

std::string Object::render(int playerIndex) const
{
    // TODO: Actually render template
    return getTemplate();
}

}
