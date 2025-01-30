#pragma once

#include <pybind11/embed.h>
#include <pugixml.hpp>

#include <string>

namespace Spielbrett {

namespace Runtime {

class IObject;
class IRuntime;

}

class Board final
{
public:
    class Object final
    {
    public:
        using Id = std::size_t;

        using State = std::unordered_map<std::string, double>;
        using Action = std::pair<std::string, std::vector<std::string>>;

        std::string getName() const;
        Id getId() const;

        std::shared_ptr<Runtime::IObject> getRuntimeObject() const;

        std::weak_ptr<Object> getParent() const;
        std::vector<std::weak_ptr<Object>> getChildren() const;

        State getState() const;
        void setState(const std::string &key, double value);

        void move(Board::Object::Id newParentId, int order);

        std::vector<Action> getAllActions() const;
        std::vector<Action> getValidActions(int playerIndex) const;
        void performAction(int playerIndex, const Action &action);

        State observe(int playerIndex) const;
        std::string render(int playerIndex) const;

    private:
        Object(const std::string &name, Board &board, Id id);
    
        void setRuntimeObject(std::shared_ptr<Runtime::IObject> runtimeObject);

        std::string name;
        Board &board;
        Id id;

        std::shared_ptr<Runtime::IObject> runtimeObject;

        std::weak_ptr<Object> parent;
        std::vector<std::weak_ptr<Object>> children;
        
        std::unordered_map<std::string, double> state;

        friend class Board;
    };

    using Action = std::tuple<Object::Id, std::string, std::vector<std::string>>;

    Board(Runtime::IRuntime &runtime, const std::string &blueprintXml, const std::unordered_map<std::string, std::string> &templates);

    // TODO: Copy and move constructors

    bool hasPrivateInformation() const;
    int numDistinctActions() const;

    void move(Object::Id objectId, Object::Id newParent, int order);

    void performAction(int playerIndex, const Action &action);
    std::string render(int playerIndex) const;

private:
    std::shared_ptr<Object> getRoot() const;

    // Objects are assigned IDs according to their order in the breadth-first traversal of the blueprint XML
    std::vector<std::shared_ptr<Object>> objects;

    std::vector<Action> actions;
};

}
