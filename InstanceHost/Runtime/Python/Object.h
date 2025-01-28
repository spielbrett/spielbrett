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

    std::string getTemplate() const;
    void setTemplate(const std::string &templateStr);

    std::string render(int playerIndex) const;

private:
    Board::Object *boardObject;
    std::string templateStr;
};

}
