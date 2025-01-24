#pragma once

#include "Object.h"

class ObjectFactory
{
public:
    ObjectFactory();

    Object construct(const pugi::xml_node &node);

    static ObjectFactory defaultFactory();
};
