#pragma once

#include "Runtime/IObject.h"

#include <pybind11/embed.h>
#include <pugixml.hpp>

#include <string>

using ActionArgs = std::vector<std::string>;
using Action = std::pair<std::string, ActionArgs>;

namespace Spielbrett {

namespace Runtime {

class IRuntime;

}

class Board final
{
public:
    class Object final
    {
    public:
        std::string getName() const;

        void move(std::weak_ptr<Object> newParent, int order);

        std::string render(int playerIndex) const;

    private:
        Object(const std::string &name, Board &board, std::size_t indexInBoard);
    
        void setRuntimeObject(std::shared_ptr<Runtime::IObject> runtimeObject);

        std::string name;
        Board &board;
        std::size_t indexInBoard;

        std::shared_ptr<Runtime::IObject> runtimeObject;

        std::weak_ptr<Object> parent;
        std::vector<std::weak_ptr<Object>> children;

        friend class Board;
    };

    Board(Runtime::IRuntime &runtime, const std::string &blueprintXml, const std::unordered_map<std::string, std::string> &templates);

    // TODO: Copy and move constructors

    bool hasPrivateInformation() const;
    int numDistinctActions() const;

    bool performAction(int playerIndex, const std::string &action, const ActionArgs &args);
    std::string render(int playerIndex) const;

private:
    std::shared_ptr<Object> getRoot() const;

    std::vector<std::shared_ptr<Object>> objects;
    std::vector<Action> actions;
};

}
