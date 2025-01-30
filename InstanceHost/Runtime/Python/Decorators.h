#pragma once

#include <pybind11/pybind11.h>

namespace Spielbrett::Runtime::Python {

enum class MethodType
{
    NONE = 0,
    OBSERVATION = 1,
    ACTION = 2
};

pybind11::function observation(pybind11::args args, pybind11::kwargs kwargs);
pybind11::function action(pybind11::args args);

}