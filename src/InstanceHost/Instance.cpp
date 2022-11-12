#include "Instance.h"

#include <stdexcept>

Instance::Instance(const std::string &instanceType)
{
    try {
        instanceModule = boost::python::import(instanceType.c_str());
    }
    catch (const boost::python::error_already_set &) {
        throw std::runtime_error("could not import Python module");
    }
}
