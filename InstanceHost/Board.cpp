#include "Board.h"
#include "Runtime/IObject.h"

#include <pybind11/cast.h>

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

namespace Spielbrett {

Board::Board(Runtime::IRuntime &runtime, const std::string &blueprintXml)
{
    pugi::xml_document doc;

    doc.load_string(blueprintXml.c_str());
}

bool Board::hasPrivateInformation() const
{
    throw std::logic_error("not implemented");
}

int Board::numDistinctActions() const
{
    return actions.size();
}

bool Board::performAction(int playerIndex, const std::string &action, const ActionArgs &args)
{
    throw std::logic_error("not implemented");
}

std::string Board::render(int playerIndex) const
{
    throw std::logic_error("not implemented");
}

}
