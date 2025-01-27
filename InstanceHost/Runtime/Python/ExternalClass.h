#pragma once

#include "../IObject.h"
#include "../../Object.h"

#include <pybind11/embed.h>

#include <string>

namespace Spielbrett::Runtime::Python {

class Board;

class ExternalClass
{
public:
    class Object : public Runtime::IObject
    {
    public:
        void performAction(int playerIndex, const std::string &action, const std::vector<std::string> &args) override;
        double getObservation(int playerIndex, const std::string &observation) override;
        std::string render(int playerIndex) override;

    private:
        Object(pybind11::object &pyClass);

        Object(const Object &) = delete;
        Object &operator=(const Object &) = delete;

        Object(Object &&) = delete;
        Object &operator=(Object &&) = delete;

        void link(std::weak_ptr<Spielbrett::Object> linkedObject);

        // Instantiating the object acquires the GIL. It is then held throughout the whole lifetime of the object.
        // Destructors are called in reverse order, so gil_scoped_acquire must preceed the instantiated pybind11::object
        pybind11::gil_scoped_acquire acquire{};

        pybind11::object pyObject;

        friend class ExternalClass;
    };

    ExternalClass(const std::string &moduleName, const std::string &className);
    ~ExternalClass();

    std::unique_ptr<Object> instantiateAndLink(std::weak_ptr<Spielbrett::Object> linkedObject);

private:
    ExternalClass(const ExternalClass &other) = delete;
    ExternalClass &operator=(const ExternalClass &other) = delete;

    ExternalClass(ExternalClass &&other) = delete;
    ExternalClass &operator=(ExternalClass &&other) = delete;

    std::unique_ptr<pybind11::object> pyClass;
};

}