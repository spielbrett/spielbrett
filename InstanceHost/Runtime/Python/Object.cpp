#include "Object.h"
#include "Decorators.h"
#include "ExternalClass.h"

#include <unordered_set>

using namespace pybind11::literals;

namespace {

// TODO: Deduce this automatically
static const std::unordered_set<std::string> DEFINED_PUBLIC_ATTRIBUTES = {
    "parent",
    "children",
    "move"
};

std::optional<pybind11::module> builtins = std::nullopt;

pybind11::module getBuiltins()
{
    if (!builtins.has_value()) {
        builtins = pybind11::module_::import("builtins");
    }
    return builtins.value();
}

std::optional<pybind11::module> itertools = std::nullopt;

pybind11::module getItertools()
{
    if (!itertools.has_value()) {
        itertools = pybind11::module_::import("itertools");
    }
    return itertools.value();
}

std::optional<pybind11::module> jinja2 = std::nullopt;

pybind11::module getJinja2()
{
    if (!jinja2.has_value()) {
        jinja2 = pybind11::module_::import("jinja2");
    }
    return jinja2.value();
}

}

namespace Spielbrett::Runtime::Python {

Object::Object()
{
}

pybind11::object Object::getAttr(pybind11::str name) const
{
    auto state = getState();
    if (state.contains(name)) {
        return state[name];
    }
    else {
        throw pybind11::attribute_error(std::format("attribute {} not found", name.cast<std::string>()));
    }
}

void Object::setAttr(pybind11::object self, pybind11::str name, pybind11::object value)
{
    if (name.cast<std::string>() == "__state") {
        getBuiltins().attr("object").attr("__setattr__")(self, name, value);
    }
    else if (self.attr("__state").contains(name)) {
        self.attr("__state")[name] = value;
    }
    else {
        getBuiltins().attr("object").attr("__setattr__")(self, name, value);
    }
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

void Object::setTemplate(pybind11::str templateStr)
{
    this->templateObj = getJinja2().attr("Template")(templateStr);
}

pybind11::object Object::getId() const
{
    if (boardObject != nullptr) {
        return pybind11::cast(boardObject->getId());
    }
    return pybind11::none{};
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


void Object::setState(pybind11::str key, pybind11::float_ value)
{
    if (boardObject != nullptr) {
        boardObject->setState(key, value);
    }
}

void Object::move(pybind11::object newParent, pybind11::int_ order)
{
    if (boardObject != nullptr) {
        boardObject->move(newParent.attr("__id").cast<Board::Object::Id>(), order);
    }
}

pybind11::str Object::render(pybind11::int_ playerIndex) const
{
    if (boardObject != nullptr) {
        return boardObject->render(playerIndex);
    }
    return "";
}

pybind11::list Object::getObservations(pybind11::object self)
{
    pybind11::list observations;

    for (auto methodName : getDecoratedMethods(self)) {
        auto method = self.attr(methodName);
        auto methodType = pybind11::getattr(method, "_method_type").cast<MethodType>();
        if (methodType != MethodType::OBSERVATION) {
            continue;
        }
        observations.append(methodName);
    }

    return observations;
}

pybind11::dict Object::observe(pybind11::object self, pybind11::int_ playerIndex)
{
    pybind11::dict observedState;

    // TODO: Add state in public information games
    // observedState.attr("update")(self.attr("__state"));

    for (auto methodName : getDecoratedMethods(self)) {
        auto method = self.attr(methodName);
        auto methodType = pybind11::getattr(method, "_method_type").cast<MethodType>();
        if (methodType != MethodType::OBSERVATION) {
            continue;
        }
        auto visible= method.attr("_visible");
        if (pybind11::isinstance<pybind11::function>(visible) && visible(playerIndex) || visible.cast<bool>()) {
            observedState[methodName] = method(playerIndex);
        }
    }

    return observedState;
}

pybind11::str Object::renderContents(pybind11::object self, pybind11::int_ playerIndex)
{
    pybind11::list childRenders;
    for (auto child : self.attr("children")) {
        childRenders.append(child.attr("_render")(playerIndex));
    }

    return self.attr("__template").attr("render")(
        "player_index"_a = playerIndex,
        "children"_a = childRenders,
        "score"_a = self.attr("score"),
        **observe(self, playerIndex));
}

pybind11::list Object::getDecoratedMethods(pybind11::object self)
{
    pybind11::list methods;

    for (auto memberName : self.attr("__dir__")()) {
        if (memberName.attr("startswith")("_").cast<bool>()) {
            continue;
        }
        if (DEFINED_PUBLIC_ATTRIBUTES.contains(memberName.cast<std::string>())) {
            continue;
        }
        auto attr = self.attr(memberName);
        if (!pybind11::isinstance<pybind11::function>(attr)) {
            continue;
        }
        if (pybind11::hasattr(self.attr(memberName), "_method_type")) {
            methods.append(memberName);
        }
    }

    return methods;
}

pybind11::list Object::getActions(pybind11::object self)
{
    pybind11::list actions;

    for (auto methodName : getDecoratedMethods(self)) {
        auto method = self.attr(methodName);
        auto methodType = pybind11::getattr(method, "_method_type").cast<MethodType>();
        if (methodType != MethodType::ACTION) {
            continue;
        }
        pybind11::list args;
        for (const auto &argTuple : method.attr("_args")) {
            auto selector = argTuple.cast<pybind11::tuple>()[0];
            if (pybind11::isinstance<pybind11::function>(selector)) {
                args.append(getBuiltins().attr("enumerate")(selector()));
            }
            else {
                args.append(getBuiltins().attr("enumerate")(selector));
            }
        }
        for (auto argSet : getItertools().attr("product")(*args)) {
            actions.append(pybind11::make_tuple(methodName, argSet));
        }
    }

    return actions;
}

pybind11::list Object::getValidActions(pybind11::object self, pybind11::int_ playerIndex)
{
    pybind11::list actions = getActions(self);
    pybind11::list validActions;

    for (const auto &action : actions) {
        auto actionTuple = action.cast<pybind11::tuple>();
        auto actionName = actionTuple[0];
        auto actionArgs = actionTuple[1].cast<pybind11::tuple>();

        for (size_t i = 0; i < pybind11::len(actionArgs); i++) {
            auto validator = self.attr(actionName).attr("_args").cast<pybind11::tuple>()[i].cast<pybind11::tuple>()[1];
            bool valid;
            if (pybind11::isinstance<pybind11::function>(validator)) {
                pybind11::list pyActionArgs;
                for (size_t j = 0; j < i; j++) {
                    pyActionArgs.append(actionArgs[j].cast<pybind11::tuple>()[1]);
                }
                valid = validator(playerIndex, *pyActionArgs).cast<bool>();
            }
            else {
                valid = validator.cast<bool>();
            }
            if (valid) {
                validActions.append(action);
            }
        }
    }
    
    return validActions;
}

}
