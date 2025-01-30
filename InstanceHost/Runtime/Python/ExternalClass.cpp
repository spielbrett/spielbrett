#include "ExternalClass.h"

#include <memory>
#include <pybind11/stl.h>

namespace Spielbrett::Runtime::Python {

ExternalClass::ExternalClass(const std::string &moduleName, const std::string &className)
{
    pybind11::gil_scoped_acquire acquire{};

    auto module = pybind11::module_::import(moduleName.c_str());
    pyClass = std::make_unique<pybind11::object>(module.attr(pybind11::str(className)));
}

ExternalClass::~ExternalClass()
{
    pybind11::gil_scoped_acquire acquire{};

    pyClass = nullptr;
}

std::unique_ptr<ExternalClass::Object> ExternalClass::instantiateAndLink(Spielbrett::Board::Object *boardObject)
{
    // GIL will be acquired by the ExternalClass::Object
    auto object = std::unique_ptr<ExternalClass::Object>(new ExternalClass::Object(*pyClass));
    object->linkBoardObject(boardObject);
    return object;
}

ExternalClass::Object::Object(pybind11::object &pyClass)
{
    // Note that we don't acquire GIL here because the gil_scoped_acquire is already defined as a member
    pyObject = pyClass();
}

pybind11::object &ExternalClass::Object::operator*()
{
    return pyObject;
}

pybind11::object *ExternalClass::Object::operator->()
{
    return &pyObject;
}

void ExternalClass::Object::linkBoardObject(Spielbrett::Board::Object *boardObject)
{
    // TODO: There must certainly be a safer and saner way to do this?
    pyObject.attr("__board_object") = reinterpret_cast<std::uintptr_t>(boardObject);
}

void ExternalClass::Object::setTemplate(const std::string &templateStr)
{
    pyObject.attr("__template") = templateStr;
}

std::vector<Board::Object::Action> ExternalClass::Object::getAllActions()
{
    return pyObject.attr("__actions").cast<std::vector<Board::Object::Action>>();
}

std::vector<Board::Object::Action> ExternalClass::Object::getValidActions(int playerIndex)
{
    return pyObject.attr("__get_valid_actions")(playerIndex).cast<std::vector<Board::Object::Action>>();
}

void ExternalClass::Object::performAction(int playerIndex, const Board::Object::Action &action)
{
    const auto &[actionName, actionArgs] = action;
    pyObject.attr(pybind11::cast(actionName))(*pybind11::cast(actionArgs));
}

Board::Object::State ExternalClass::Object::observe(int playerIndex)
{
    return pyObject.attr("__observe")(playerIndex).cast<Board::Object::State>();
}

std::string ExternalClass::Object::renderContents(int playerIndex)
{
    return pyObject.attr("_render_contents")(playerIndex).cast<std::string>();
}

}
