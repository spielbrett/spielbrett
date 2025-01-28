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
        Board::Object::Id objectId,
        const std::string &action,
        const ActionArgs &args);

    std::unordered_map<UserID, std::string> render() const;
    std::string render(const UserID &userId) const;

private:
    std::string doRender(const UserID &userId) const;

    std::vector<UserID> userIds;
    std::unordered_map<UserID, int> playerIndices;

    Runtime::Python::Runtime runtime;
    std::unique_ptr<Board> board;
    std::shared_ptr<const OpenSpielGame> openSpielGame;

    std::vector<std::pair<UserID, Action>> history;

    mutable std::shared_mutex sm;
};

}
