#pragma once

#include "../../Board.h"

namespace Spielbrett::Runtime::Python
{

class Object
{
public:
    Object();

    std::string render(int playerIndex) const;

    pybind11::object getParent() const;
    pybind11::list getChildren() const;

    pybind11::dict getState() const;
    void setState(const std::string &key, double value);

    void move(pybind11::object newParent, int order);

    Board::Object *getBoardObject() const;
    void setBoardObject(Board::Object *boardObject);

    pybind11::object getTemplate() const;
    void setTemplate(const std::string &templateStr);

    Board::Object::Id getId() const;

    static pybind11::str renderTemplate(pybind11::object self, int playerIndex);

private:
    static pybind11::module getJinja2();

    Board::Object *boardObject;
    pybind11::object templateObj;

    static std::optional<pybind11::module> jinja2;
};

}
