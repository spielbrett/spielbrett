#include "Object.h"

#include <pybind11/pybind11.h>

using namespace Spielbrett::Runtime::Python;

PYBIND11_EMBEDDED_MODULE(spielbrett, m)
{
    pybind11::class_<Object>(m, "Object")
        .def(pybind11::init<>())
        .def_property(
            "__board_object",
            [](const Object &object) -> std::uintptr_t {
                return reinterpret_cast<std::uintptr_t>(object.getBoardObject());
            },
            [](Object &object, std::uintptr_t value) {
                object.setBoardObject(reinterpret_cast<Spielbrett::Board::Object *>(value));
            });
}
