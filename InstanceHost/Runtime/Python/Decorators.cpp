#include "Decorators.h"

namespace Spielbrett::Runtime::Python {

pybind11::function observation(pybind11::args args, pybind11::kwargs kwargs) 
{
    if (args.size() == 1 && kwargs.size() == 0) {
        auto f = args[0];
        f.attr("_method_type") = MethodType::OBSERVATION;
        f.attr("_visible") = true;
        return f;
    } else {
        return pybind11::cpp_function([args, kwargs](pybind11::function f) -> pybind11::function {
            f.attr("_method_type") = MethodType::OBSERVATION;
            f.attr("_visible") = kwargs["visible"];
            return f;
        });
    }
}

pybind11::function action(pybind11::args args) 
{
    if (args.size() == 1) {
        auto f = args[0];
        f.attr("_method_type") = MethodType::ACTION;
        f.attr("_args") = pybind11::make_tuple();
        return f;
    } else {
        return pybind11::cpp_function([args](pybind11::function f) -> pybind11::function {
            f.attr("_method_type") = MethodType::ACTION;
            f.attr("_args") = args;
            return f;
        });
    }
}

}