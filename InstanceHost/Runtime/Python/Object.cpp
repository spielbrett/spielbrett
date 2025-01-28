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

pybind11::object Object::getTemplate() const
{
    return templateObj;
}

void Object::setTemplate(const std::string &templateStr)
{
    this->templateObj = getJinja2().attr("Template")(templateStr);
}

pybind11::module Object::getJinja2()
{
    if (!Object::jinja2.has_value()) {
        Object::jinja2 = pybind11::module_::import("jinja2");
    }
    return Object::jinja2.value();
}

std::optional<pybind11::module> Object::jinja2 = std::nullopt;

}
