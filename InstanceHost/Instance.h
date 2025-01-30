#pragma once

#include "Board.h"

#include "OpenSpielGame.h"
#include "Runtime/Python/Runtime.h"

#include <pybind11/embed.h>

#include <shared_mutex>
#include <string>
#include <unordered_map>

namespace Spielbrett {

using UserID = std::string;

class Instance final
{
public:
    Instance(
        const std::string &instanceType,
        const std::vector<UserID> &userIds);

    void performAction(
        const UserID &userId,
        const Board::Action &action);

    std::unordered_map<UserID, std::pair<std::string, std::vector<Board::Action>>> render() const;
    std::pair<std::string, std::vector<Board::Action>> render(const UserID &userId) const;

private:
    std::pair<std::string, std::vector<Board::Action>> doRender(const UserID &userId) const;

    std::vector<UserID> userIds;
    std::unordered_map<UserID, int> playerIndices;

    Runtime::Python::Runtime runtime;
    std::unique_ptr<Board> board;
    std::shared_ptr<const OpenSpielGame> openSpielGame;

    std::vector<std::pair<UserID, Board::Action>> history;

    mutable std::shared_mutex sm;
};

}
