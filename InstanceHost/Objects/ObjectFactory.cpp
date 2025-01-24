#include "ObjectFactory.h"

#include "Object.h"

#include <optional>

namespace
{

std::optional<ObjectFactory> defaultFactory;

}

ObjectFactory::ObjectFactory()
{
}

Object ObjectFactory::construct(const pugi::xml_node &node)
{
    return Object(node);
}

ObjectFactory ObjectFactory::defaultFactory()
{
    if (!::defaultFactory.has_value()) {
        ::defaultFactory = ObjectFactory();
    }
    return ::defaultFactory.value();
}
