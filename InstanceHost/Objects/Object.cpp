#include "Object.h"

Object::Object(const pugi::xml_node &node) :
    name(node.name())
{
    for (const auto child : node.children()) {
        children.push_back(std::make_shared<Object>(child));
    }
}

void Object::render(pugi::xml_node &node) const
{
    node.set_name(name.c_str());

    for (const auto child : children) {
        auto childNode = node.append_child();
        child->render(childNode);
    }
}
