#ifndef BOARD_H
#define BOARD_H

#include "BoardObjects/Object.h"
#include "PyGameClass.h"

#include <pybind11/embed.h>

#include <pugixml.hpp>

#include <stack>
#include <string>

class Board
{
public:
    Board(const std::string &xml);

    std::string render(PyGameClass &gameClass, int playerIndex) const;

    std::unique_ptr<Board> stripPresentation() const;
    std::unique_ptr<Board> clone() const;

    bool hasPrivateInformation() const;
    int numDistinctActions() const;

private:
    std::vector<Object> layout;
    std::vector<Object> publicInformation;
    std::vector<Object> privateInformation;
};

#endif // BOARD_H
