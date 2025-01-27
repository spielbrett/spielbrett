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
        const std::string &action,
        const ActionArgs &args);

    std::unordered_map<UserID, std::string> render() const;
    std::string render(const UserID &userId) const;

private:
    Runtime::Python::Runtime runtime;
    std::unique_ptr<Board> board;
    std::vector<std::pair<UserID, Action>> history;

    std::vector<UserID> userIds;
    std::unordered_map<UserID, int> playerIndices;

    std::shared_ptr<const OpenSpielGame> openSpielGame;

    mutable std::shared_mutex sm;

    std::string doRender(const UserID &userId) const;
};

}
