#ifndef INSTANCE_H
#define INSTANCE_H

#include "Board.h"

#include "OpenSpielGame.h"
#include "PyGameClass.h"

#include <pybind11/embed.h>

#include <shared_mutex>
#include <string>
#include <unordered_map>

class Instance
{
public:
    Instance(
        const std::string &instanceType,
        const std::vector<std::string> &userIds);

    void performAction(
        const std::string &userId,
        const std::string &action);

    std::unordered_map<std::string, std::string> renderMarkup() const;
    std::string renderMarkup(const std::string &userId) const;

private:
    std::unique_ptr<PyGameClass> gameClass;
    std::unique_ptr<Board> board;

    std::vector<std::string> userIds;
    std::unordered_map<std::string, int> playerIndices;

    std::shared_ptr<const OpenSpielGame> openSpielGame;

    mutable std::shared_mutex sm;

    std::string doRenderMarkup(const std::string &userId) const;
};

#endif // INSTANCE_H
