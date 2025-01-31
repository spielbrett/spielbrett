#pragma once

#include "../IObject.h"
#include "../../Board.h"

#include <pybind11/embed.h>

#include <string>

namespace Spielbrett::Runtime::Python {

class ExternalClass
{
public:
    class Object : public Runtime::IObject
    {
    public:
        pybind11::object &operator*();
        pybind11::object *operator->();

        void setTemplate(const std::string &templateStr) override;

        std::vector<Board::Object::Action> getAllActions() override;
        std::vector<Board::Object::Action> getValidActions(int playerIndex) override;
        void performAction(int playerIndex, const Board::Object::Action &action) override;

        std::vector<std::string> getAllObservations() override;
        Board::Object::State observe(int playerIndex) override;
        std::string renderContents(int playerIndex) override;

        double score(int playerIndex) override;

    private:
        Object(pybind11::object &pyClass);

        Object(const Object &) = delete;
        Object &operator=(const Object &) = delete;

        Object(Object &&) = delete;
        Object &operator=(Object &&) = delete;

        void linkBoardObject(Spielbrett::Board::Object *boardObject);

        // Instantiating the object acquires the GIL. It is then held throughout the whole lifetime of the object.
        // Destructors are called in reverse order, so gil_scoped_acquire must preceed the instantiated pybind11::object
        // TODO: GIL should be acquired in more granular manner
        pybind11::gil_scoped_acquire acquire{};

        pybind11::object pyObject;

        friend class ExternalClass;
    };

    ExternalClass(const std::string &moduleName, const std::string &className);
    ~ExternalClass();

    std::unique_ptr<Object> instantiateAndLink(Spielbrett::Board::Object *boardObject);

private:
    ExternalClass(const ExternalClass &other) = delete;
    ExternalClass &operator=(const ExternalClass &other) = delete;

    std::unique_ptr<pybind11::object> pyClass;
};

}