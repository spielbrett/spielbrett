#pragma once

#include "../../Board.h"

namespace Spielbrett::Runtime::Python
{

class Object
{
public:
    Object();

    Board::Object *getBoardObject() const;
    void setBoardObject(Board::Object *boardObject);

    pybind11::object getTemplate() const;
    void setTemplate(const std::string &templateStr);

    std::string render(pybind11::object self, int playerIndex) const;

private:
    static pybind11::module getJinja2();

    Board::Object *boardObject;
    pybind11::object templateObj;

    static std::optional<pybind11::module> jinja2;
};

}
