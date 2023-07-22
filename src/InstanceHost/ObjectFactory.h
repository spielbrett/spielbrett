#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include "BoardObjects/Object.h"

class ObjectFactory
{
public:
    ObjectFactory();

    Object construct(const pugi::xml_node &node);

    static ObjectFactory defaultFactory();
};

#endif // OBJECT_FACTORY_H
