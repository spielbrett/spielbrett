#pragma once

#include "Objects/Object.h"
#include "PyGameClass.h"

#include <pybind11/embed.h>

#include <pugixml.hpp>

#include <stack>
#include <string>

using ActionArgs = std::vector<std::string>;
using Action = std::pair<std::string, ActionArgs>;

class Board
{
public:
    Board(const std::string &xml);

    std::string render(PyGameClass &gameClass, int playerIndex) const;

    std::unique_ptr<Board> stripPresentation() const;
    std::unique_ptr<Board> clone() const;

    bool hasPrivateInformation() const;
    int numDistinctActions() const;

    bool tryPerformNativeAction(int playerIndex, const std::string &action, const ActionArgs &args);

private:
    std::vector<Object> layout;
    std::vector<Object> publicInformation;
    std::vector<Object> privateInformation;
};
