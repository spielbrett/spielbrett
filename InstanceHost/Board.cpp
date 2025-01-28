#include "Board.h"
#include "Runtime/IObject.h"
#include "Runtime/IRuntime.h"

#include <pybind11/cast.h>

#include <memory>
#include <stdexcept>
#include <string>

namespace Spielbrett {

Board::Board(Runtime::IRuntime &runtime, const std::string &blueprintXml, const std::unordered_map<std::string, std::string> &templates)
{
    pugi::xml_document doc;

    doc.load_string(blueprintXml.c_str());
    if (!doc.first_child() || doc.first_child().next_sibling()) {
        throw std::runtime_error("XML must have exactly one root element");
    }

    std::queue<std::pair<pugi::xml_node, std::optional<std::size_t>>> queue;
    queue.emplace(doc.first_child(), std::nullopt);

    while (!queue.empty()) {
        auto [node, parentIndex] = queue.front();
        queue.pop();

        auto objectIndex = objects.size();
        auto &object = objects.emplace_back(new Object(node.name(), *this, objectIndex));

        auto runtimeObject = runtime.createAndLinkObject(node.name(), object.get());
        runtimeObject->setTemplate(templates.at(node.name()));
        object->setRuntimeObject(std::move(runtimeObject));

        if (parentIndex.has_value()) {
            auto &parent = objects[parentIndex.value()];
            parent->children.push_back(object);
            object->parent = parent;
        }

        for (auto child = node.first_child(); !child.empty(); child = child.next_sibling()) {
            queue.emplace(child, objectIndex);
        }
    }
}

bool Board::hasPrivateInformation() const
{
    // TODO: Implement this
    return false;
}

int Board::numDistinctActions() const
{
    return actions.size();
}

bool Board::performAction(int playerIndex, const std::string &action, const ActionArgs &args)
{
    throw std::logic_error("not implemented");
}

std::string Board::render(int playerIndex) const
{
    return getRoot()->render(playerIndex);
}

std::shared_ptr<Board::Object> Board::getRoot() const
{
    return objects[0];
}

Board::Object::Object(const std::string &name, Board &board, std::size_t indexInBoard) :
    name(name), board(board), indexInBoard(indexInBoard)
{
}

std::string Board::Object::getName() const
{
    return name;
}

std::string Board::Object::render(int playerIndex) const
{
    return runtimeObject->render(playerIndex);
}

void Board::Object::setRuntimeObject(std::shared_ptr<Runtime::IObject> runtimeObject)
{
    this->runtimeObject = runtimeObject;
}

}
