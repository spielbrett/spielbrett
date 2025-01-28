#include "Decorators.h"

namespace Spielbrett::Runtime::Python {

pybind11::function observation(pybind11::function f) 
{
    f.attr("is_observation") = true;
    return f;
}

}