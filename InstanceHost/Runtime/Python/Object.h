#pragma once

#include "../../Object.h"

#include <memory>

namespace Spielbrett::Runtime::Python
{

class Object
{
public:
    std::weak_ptr<Spielbrett::Object> __linked_object;
};

}
