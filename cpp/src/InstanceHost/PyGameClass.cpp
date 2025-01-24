#include "PyGameClass.h"

#include <sstream>

PyGameClass::PyGameClass(const std::string &moduleName, const std::string &className)
{
    pybind11::gil_scoped_acquire acquire{};

    auto gameModule = pybind11::module_::import(moduleName.c_str());
    gameClass = std::make_unique<pybind11::object>(gameModule.attr(pybind11::str(className)));
}

PyGameClass::~PyGameClass()
{
    pybind11::gil_scoped_acquire acquire{};

    gameClass = nullptr;
}

PyGameClass::Object PyGameClass::instantiate(const Board &board)
{
    return Object(*gameClass, board);
}

PyGameClass::Object::Object(pybind11::object &gameClass, const Board &board)
{
    // TODO: Implement Python board object to pass to the game class
    gameObject = gameClass(pybind11::none());
}

pybind11::object &PyGameClass::Object::operator*()
{
    return gameObject;
}

pybind11::object *PyGameClass::Object::operator->()
{
    return &gameObject;
}
