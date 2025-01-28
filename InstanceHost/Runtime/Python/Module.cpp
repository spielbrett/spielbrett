#include "Object.h"
#include "Decorators.h"

#include <pybind11/pybind11.h>

using namespace Spielbrett::Runtime::Python;

PYBIND11_EMBEDDED_MODULE(spielbrett, m)
{
    pybind11::class_<Object>(m, "Object")
        .def(pybind11::init<>())
        .def("render", &Object::render)
        .def_property_readonly("parent", &Object::getParent)
        .def_property_readonly("children", &Object::getChildren)
        .def_property("state", &Object::getState, &Object::setState)
        .def("move", &Object::move)
        .def_property(
            "__board_object",
            [](const Object &object) -> std::uintptr_t {
                return reinterpret_cast<std::uintptr_t>(object.getBoardObject());
            },
            [](Object &object, std::uintptr_t value) -> void {
                object.setBoardObject(reinterpret_cast<Spielbrett::Board::Object *>(value));
            })
        .def_property("__template", &Object::getTemplate, &Object::setTemplate)
        .def_property_readonly("__id", &Object::getId)
        .def("__render_template", [](pybind11::object self, int playerIndex) -> std::string {
            return Object::renderTemplate(self, playerIndex);
        });

    m.def("observation", &observation);
}
