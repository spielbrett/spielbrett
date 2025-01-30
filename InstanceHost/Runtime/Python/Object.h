#pragma once

#include "../../Board.h"

namespace Spielbrett::Runtime::Python
{

class Object
{
public:
    Object();

    pybind11::object getAttr(pybind11::str name);
    static void setAttr(pybind11::object self, pybind11::str name, pybind11::object value);

    pybind11::object getParent() const;
    pybind11::list getChildren() const;
    void move(pybind11::object newParent, pybind11::int_ order);

    Board::Object *getBoardObject() const;
    void setBoardObject(Board::Object *boardObject);

    pybind11::object getTemplate() const;
    void setTemplate(pybind11::str templateStr);

    pybind11::object getId() const;

    pybind11::dict getState() const;
    void setState(pybind11::str key, pybind11::float_ value);

    pybind11::str render(pybind11::int_ playerIndex) const;

    static pybind11::dict observe(pybind11::object self, pybind11::int_ playerIndex);
    static pybind11::str renderContents(pybind11::object self, pybind11::int_ playerIndex);

private:
    static pybind11::list getDecoratedMethods(pybind11::object self);

    Board::Object *boardObject;
    pybind11::object templateObj;
};

}
