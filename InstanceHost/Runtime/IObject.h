#pragma once

#include "../Board.h"

#include <string>

namespace Spielbrett::Runtime {

class IObject {
public:
    virtual ~IObject() = default;

    virtual void setTemplate(const std::string &templateStr) = 0;

    virtual std::vector<Board::Object::Action> getAllActions() = 0;
    virtual std::vector<Board::Object::Action> getValidActions(int playerIndex) = 0;
    virtual void performAction(int playerIndex, const Board::Object::Action &action) = 0;

    virtual std::vector<std::string> getAllObservations() = 0;
    virtual Board::Object::State observe(int playerIndex) = 0;
    virtual std::string renderContents(int playerIndex) = 0;

    virtual double score(int playerIndex) = 0;
};

}