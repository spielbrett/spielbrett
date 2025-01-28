#include "Object.h"

#include <pybind11/pybind11.h>

using namespace Spielbrett::Runtime::Python;

using namespace pybind11::literals;

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
            })
        .def_property("__template", &Object::getTemplate, &Object::setTemplate)
        .def("render", [](pybind11::object self, int playerIndex) {
            pybind11::dict context("playerIndex"_a = playerIndex);
            context.attr("update")(self.attr("__dict__"));
            return self.attr("__template").attr("render")(**context).cast<std::string>();
        });
}
