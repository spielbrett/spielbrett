#include "Object.h"
#include "Decorators.h"

#include <pybind11/pybind11.h>

using namespace Spielbrett::Runtime::Python;

PYBIND11_EMBEDDED_MODULE(spielbrett, m)
{
    pybind11::class_<Object>(m, "Object")
        .def(pybind11::init<>())
        .def("__getattr__", &Object::getAttr)
        .def("__setattr__", &Object::setAttr)
        .def_property_readonly("parent", &Object::getParent)
        .def_property_readonly("children", &Object::getChildren)
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
        .def_property("__state", &Object::getState, &Object::setState)
        .def_property_readonly("__observations", &Object::getObservations)
        .def("__observe", &Object::observe)
        .def("_render", &Object::render)
        .def("_render_contents", &Object::renderContents)
        .def_property_readonly("__actions", &Object::getActions)
        .def("__get_valid_actions", &Object::getValidActions);

    pybind11::enum_<MethodType>(m, "MethodType")
        .value("None", MethodType::NONE)
        .value("Observation", MethodType::OBSERVATION)
        .value("Action", MethodType::ACTION)
        .export_values();

    m.def("observation", &observation);
    m.def("action", &action);

    m.attr("PLAYER_INDEX_CHANCE") = -1;
    m.attr("PLAYER_INDEX_SIMULTANEOUS") = -2;
}
