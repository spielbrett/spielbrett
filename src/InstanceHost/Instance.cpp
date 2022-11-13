#include "Instance.h"

#include <sstream>
#include <stdexcept>

Instance::Instance(const std::string &instanceType)
{
    try {
        instanceModule = boost::python::import(instanceType.c_str());
    }
    catch (const boost::python::error_already_set &) {
        if (PyErr_ExceptionMatches(PyExc_ImportError)) {
            std::stringstream ss;
            ss << "failed to import module " << instanceType;
            throw std::invalid_argument(ss.str());
        }
        else {
            throw std::runtime_error("Python exception occured");
        }
    }
}

void Instance::performAction(
    const std::string &userId,
    const std::string &actionName,
    const std::string &payload)
{
}