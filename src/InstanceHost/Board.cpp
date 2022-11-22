#include "Board.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

Board::Board(const std::string &xml)
{
    doc.load_string(xml.c_str());
}

std::string Board::render(PyGameClass &gameClass, int playerIndex) const
{
    std::stringstream ss;
    doc.save(ss);
    return ss.str();
}

std::unique_ptr<Board> Board::stripPresentation() const
{
    throw std::logic_error("not implemented");
}

std::unique_ptr<Board> Board::clone() const
{
    throw std::logic_error("not implemented");
}

bool Board::hasPrivateInformation() const
{
    throw std::logic_error("not implemented");
}

int Board::numDistinctActions() const
{
    throw std::logic_error("not implemented");
}
