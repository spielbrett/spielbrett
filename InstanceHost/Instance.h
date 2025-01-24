#pragma once

#include "Board.h"

#include "OpenSpielGame.h"
#include "PyGameClass.h"

#include <pybind11/embed.h>

#include <shared_mutex>
#include <string>
#include <unordered_map>

using UserID = std::string;

class Instance
{
public:
    Instance(
        const std::string &instanceType,
        const std::vector<UserID> &userIds);

    void performAction(
        const UserID &userId,
        const std::string &action,
        const ActionArgs &args);
    
    std::vector<Action> getAvailableActions() const;

    std::unordered_map<UserID, std::string> renderMarkup() const;
    std::string renderMarkup(const UserID &userId) const;

private:
    std::unique_ptr<PyGameClass> gameClass;
    std::unique_ptr<Board> board;
    std::vector<std::pair<UserID, Action>> history;

    std::vector<UserID> userIds;
    std::unordered_map<UserID, int> playerIndices;

    std::shared_ptr<const OpenSpielGame> openSpielGame;

    mutable std::shared_mutex sm;

    std::string doRenderMarkup(const UserID &userId) const;
};
