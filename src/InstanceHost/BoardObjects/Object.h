#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>

#include <pugixml.hpp>

class Object
{
public:
    Object(const pugi::xml_node &node);

    void render(pugi::xml_node &node) const;

private:
    std::string name;
    std::vector<std::shared_ptr<Object>> children;
};

#endif // OBJECT_H