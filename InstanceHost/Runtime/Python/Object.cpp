#include "Object.h"
#include "ExternalClass.h"

using namespace pybind11::literals;

namespace Spielbrett::Runtime::Python {

Object::Object()
{
}

std::string Object::render(int playerIndex) const
{
    if (boardObject != nullptr) {
        return this->boardObject->render(playerIndex);
    }
    return "";
}

pybind11::object Object::getParent() const
{
    // TODO: Safer way to do this
    if (boardObject != nullptr) {
        auto parent = boardObject->getParent().lock();
        auto pyObject = **dynamic_cast<ExternalClass::Object *>(parent->getRuntimeObject().get());
        return pyObject;
    }
    return pybind11::none{};
}

pybind11::list Object::getChildren() const
{
    pybind11::list result;
    if (boardObject != nullptr) {
        for (const auto childPtr : boardObject->getChildren()) {
            // TODO: Safer way to do this
            auto child = childPtr.lock();
            auto pyObject = **dynamic_cast<ExternalClass::Object *>(child->getRuntimeObject().get());
            result.append(pyObject);
        }
    }
    return result;
}

pybind11::dict Object::getState() const
{
    pybind11::dict state;
    if (boardObject != nullptr) {
        for (const auto &[key, value] : boardObject->getState()) {
            state[pybind11::cast(key)] = value;
        }
    }
    return state;
}

void Object::setState(const std::string &key, double value)
{
    if (boardObject != nullptr) {
        boardObject->setState(key, value);
    }
}

void Object::move(pybind11::object newParent, int order)
{
    if (boardObject != nullptr) {
        boardObject->move(newParent.attr("__id").cast<Board::Object::Id>(), order);
    }
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

Board::Object::Id Object::getId() const
{
    if (boardObject != nullptr) {
        return boardObject->getId();
    }
    return -1;
}

pybind11::str Object::renderTemplate(pybind11::object self, int playerIndex)
{
    pybind11::dict context;
    context.attr("update")(self.attr("state"));

    for (auto memberName : self.attr("__dir__")()) {
        // TODO: Handle decorator
        if (!memberName.attr("startswith")("observation_").cast<bool>()) {
            continue;
        }
        auto member = self.attr(memberName);
        context[memberName.attr("removeprefix")("observation_")] = member(playerIndex);
    }

    return self.attr("__template").attr("render")(
        "player_index"_a = playerIndex,
        "children"_a = self.attr("children"),
        **context).cast<std::string>();
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
