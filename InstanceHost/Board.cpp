#include "Board.h"
#include "Runtime/IObject.h"
#include "Runtime/IRuntime.h"

#include <pybind11/cast.h>

#include <memory>
#include <stdexcept>
#include <string>

namespace Spielbrett {

Board::Board(Runtime::IRuntime &runtime, const std::string &blueprintXml)
{
    pugi::xml_document doc;

    doc.load_string(blueprintXml.c_str());
    if (!doc.first_child() || doc.first_child().next_sibling()) {
        throw std::runtime_error("XML must have exactly one root element");
    }

    std::queue<std::pair<std::optional<std::size_t>, pugi::xml_node>> queue;
    queue.emplace(std::nullopt, doc.first_child());

    while (!queue.empty()) {
        auto [parentIndex, node] = queue.front();
        queue.pop();

        auto objectIndex = objects.size();
        auto &object = objects.emplace_back(new Object(*this, objectIndex));

        object->setRuntimeObject(runtime.createAndLinkObject(node.name(), object.get()));

        if (parentIndex.has_value()) {
            auto &parent = objects[parentIndex.value()];
            parent->children.push_back(object);
            object->parent = parent;
        }

        for (auto child = node.first_child(); !child.empty(); child = child.next_sibling()) {
            queue.emplace(objectIndex, child);
        }
    }
}

bool Board::hasPrivateInformation() const
{
    throw std::logic_error("not implemented");
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
    throw std::logic_error("not implemented");
}

Board::Object::Object(Board &board, std::size_t indexInBoard) :
    board(board), indexInBoard(indexInBoard)
{
}

void Board::Object::setRuntimeObject(std::shared_ptr<Runtime::IObject> runtimeObject)
{
    this->runtimeObject = runtimeObject;
}

}
