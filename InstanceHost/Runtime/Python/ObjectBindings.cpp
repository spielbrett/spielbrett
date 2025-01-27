#include "Object.h"

#include <pybind11/pybind11.h>

using namespace Spielbrett::Runtime::Python;

PYBIND11_MODULE(spielbrett, m)
{
    pybind11::class_<Object>(m, "Object")
        .def_readwrite("__linked_object", &Object::__linked_object);
}
