#pragma once

#include <pybind11/pybind11.h>

namespace Spielbrett::Runtime::Python {

pybind11::function observation(pybind11::function f);

}