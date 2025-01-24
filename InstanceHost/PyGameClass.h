#pragma once

#include <pybind11/embed.h>

#include <string>

class Board;

class PyGameClass
{
public:
    class Object
    {
    public:
        pybind11::object &operator*();
        pybind11::object *operator->();

    private:
        // gameClass is passed by reference to avoid acquiring GIL twice
        Object(pybind11::object &gameClass, const Board &board);

        // Disallow copying object (new one must be instantiated instead)
        Object(const Object &) = delete;
        Object &operator=(const Object &) = delete;

        // Disallow moving object (may be implemented in the future)
        Object(Object &&) = delete;
        Object &operator=(Object &&) = delete;

        // Destructors are called in reverse order, so the acquire must preceed the gameObject
        pybind11::gil_scoped_acquire acquire{};
        pybind11::object gameObject;

        friend class PyGameClass;
    };

    PyGameClass(const std::string &moduleName, const std::string &className);
    ~PyGameClass();

    // Disallow copying game class (may be implemented in the future)
    PyGameClass(const PyGameClass &) = delete;
    PyGameClass &operator=(const PyGameClass &) = delete;

    // Disallow moving game class (may be implemented in the future)
    PyGameClass(PyGameClass &&) = delete;
    PyGameClass &operator=(PyGameClass &&) = delete;

    Object instantiate(const Board &board);

private:
    std::unique_ptr<pybind11::object> gameClass;
};
