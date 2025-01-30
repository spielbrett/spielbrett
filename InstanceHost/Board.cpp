#include "Board.h"
#include "Runtime/IObject.h"
#include "Runtime/IRuntime.h"

#include <__algorithm/remove.h>
#include <iostream>
#include <pybind11/cast.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

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

        for (auto attribute = node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            object->setState(attribute.name(), std::stod(attribute.value()));
        }

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

    for (const auto &object : objects) {
        for (const auto &objectAction : object->getRuntimeObject()->getAllActions()) {
            actions.emplace_back(object->getId(), objectAction.first, objectAction.second);
        }
    }
}

bool Board::hasPrivateInformation() const
{
    // TODO: Allow this to be set to false and enforced
    return true;
}

int Board::numDistinctActions() const
{
    return actions.size();
}

void Board::move(Object::Id objectId, Object::Id newParentId, int order)
{
    auto &oldParentChildren = objects[objectId]->parent.lock()->children;
    oldParentChildren.erase(std::remove_if(oldParentChildren.begin(), oldParentChildren.end(), [objectId](auto val) {
        return val.lock()->getId() == objectId;
    }));
    objects[objectId]->parent.reset();

    auto &newParentChildren = objects[newParentId]->children;
    auto insertPos = newParentChildren.begin();
    if (order < 0) {
        order = newParentChildren.size() + order + 1;
    }
    if (order > newParentChildren.size()) {
        order = newParentChildren.size();
    }
    std::advance(insertPos, order);
    newParentChildren.insert(insertPos, objects[objectId]);
    objects[objectId]->parent = objects[newParentId];
}

void Board::performAction(int playerIndex, const Action &action)
{
    const auto &[objectId, actionName, actionArgs] = action;
    objects.at(objectId)->performAction(playerIndex, {actionName, actionArgs});
}

std::pair<std::string, std::vector<Board::Action>> Board::render(int playerIndex) const
{
    auto renderStr = getRoot()->render(playerIndex);
    std::vector<Action> actions;
    
    pugi::xml_document doc;
    doc.load_string(renderStr.c_str());

    std::queue<pugi::xml_node> queue;
    queue.push(doc.first_child());

    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();

        if (std::string(node.name()) == "Object") {
            auto idAttr = node.attribute("id");
            auto objectId = std::stoi(idAttr.value());
            auto validActions = objects.at(objectId)->getValidActions(playerIndex);
            for (const auto &action : validActions) {
                actions.emplace_back(objectId, action.first, action.second);
            }
        }

        for (auto child = node.first_child(); child; child = child.next_sibling()) {
            queue.push(child);
        }
    }

    return {renderStr, actions};
}

std::shared_ptr<Board::Object> Board::getRoot() const
{
    return objects[0];
}

Board::Object::Object(const std::string &name, Board &board, Id id) :
    name(name), board(board), id(id)
{
}

std::string Board::Object::getName() const
{
    return name;
}

Board::Object::Id Board::Object::getId() const
{
    return id;
}

std::shared_ptr<Runtime::IObject> Board::Object::getRuntimeObject() const
{
    return runtimeObject;
}

std::weak_ptr<Board::Object> Board::Object::getParent() const
{
    return parent;
}

std::vector<std::weak_ptr<Board::Object>> Board::Object::getChildren() const
{
    return children;
}

std::unordered_map<std::string, double> Board::Object::getState() const
{
    return state;
}

void Board::Object::setState(const std::string &key, double value)
{
    state[key] = value;
}

void Board::Object::move(Board::Object::Id newParentId, int order)
{
    board.move(id, newParentId, order);
}

std::vector<Board::Object::Action> Board::Object::getAllActions() const
{
    return runtimeObject->getAllActions();
}

std::vector<Board::Object::Action> Board::Object::getValidActions(int playerIndex) const
{
    return runtimeObject->getValidActions(playerIndex);
}

void Board::Object::performAction(int playerIndex, const Action &action)
{
    runtimeObject->performAction(playerIndex, action);
}

Board::Object::State Board::Object::observe(int playerIndex) const
{
    return runtimeObject->observe(playerIndex);
}

std::string Board::Object::render(int playerIndex) const
{
    auto state = observe(playerIndex);
    std::string attributes;
    for (const auto &[key, value] : state) {
        attributes += std::format(" {}=\"{}\"", key, value);
    }
    return std::format("<Object id=\"{}\"{}>{}</Object>", id, attributes, runtimeObject->renderContents(playerIndex));
}

void Board::Object::setRuntimeObject(std::shared_ptr<Runtime::IObject> runtimeObject)
{
    this->runtimeObject = runtimeObject;
}

}
