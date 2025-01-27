#pragma once

#include "Object.h"
#include "Runtime/IObject.h"
#include "Runtime/IRuntime.h"

#include <pybind11/embed.h>
#include <pugixml.hpp>

#include <string>

using ActionArgs = std::vector<std::string>;
using Action = std::pair<std::string, ActionArgs>;

namespace Spielbrett {

class Board final
{
public:
    Board(Runtime::IRuntime &runtime, const std::string &blueprintXml);

    // TODO: Copy and move constructors

    bool hasPrivateInformation() const;
    int numDistinctActions() const;

    bool performAction(int playerIndex, const std::string &action, const ActionArgs &args);
    std::string render(int playerIndex) const;

private:
    std::vector<Object> objects;
    std::vector<Action> actions;
};

}
