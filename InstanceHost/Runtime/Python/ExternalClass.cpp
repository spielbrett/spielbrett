#include "ExternalClass.h"

#include <memory>

namespace Spielbrett::Runtime::Python {

ExternalClass::ExternalClass(const std::string &moduleName, const std::string &className)
{
    pybind11::gil_scoped_acquire acquire{};

    auto module = pybind11::module_::import(moduleName.c_str());
    pyClass = std::make_unique<pybind11::object>(module.attr(pybind11::str(className)));
}

ExternalClass::~ExternalClass()
{
    pybind11::gil_scoped_acquire acquire{};

    pyClass = nullptr;
}

std::unique_ptr<ExternalClass::Object> ExternalClass::instantiateAndLink(std::weak_ptr<Spielbrett::Object> linkedObject)
{
    // GIL will be acquired by the ExternalClass::Object
    auto object = std::unique_ptr<ExternalClass::Object>(new ExternalClass::Object(*pyClass));
    object->link(linkedObject);
    return object;
}

ExternalClass::Object::Object(pybind11::object &pyClass)
{
    // Note that we don't acquire GIL here because the gil_scoped_acquire is already defined as a member
    pyObject = pyClass();
}

void ExternalClass::Object::link(std::weak_ptr<Spielbrett::Object> linkedObject)
{
    pyObject.attr("__linked_object") = linkedObject;
}

void ExternalClass::Object::performAction(int playerIndex, const std::string &action, const std::vector<std::string> &args)
{
    pyObject.attr(pybind11::cast(action))(*pybind11::cast(args));
}

double ExternalClass::Object::getObservation(int playerIndex, const std::string &observation)
{
    return pyObject.attr(pybind11::cast(observation))(playerIndex).cast<double>();
}

std::string ExternalClass::Object::render(int playerIndex)
{
    return pyObject.attr("render")(playerIndex).cast<std::string>();
}

}
