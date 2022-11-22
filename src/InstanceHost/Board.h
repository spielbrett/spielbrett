#ifndef BOARD_H
#define BOARD_H

#include "PyGameClass.h"

#include <pybind11/embed.h>

#include <pugixml.hpp>

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
    pugi::xml_document doc;
};

#endif // BOARD_H
