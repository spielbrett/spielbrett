#include "Instance.h"

#include <open_spiel/spiel.h>

#include <nlohmann/json.hpp>

#include <boost/algorithm/string.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <shared_mutex>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace
{

struct ObjectEntry {
    std::string moduleName;
    std::string className;
    std::string templatePath;
};

struct GameConfig {
    std::string blueprint;
    int minPlayers;
    int maxPlayers;
    int moveLimit;
    std::unordered_map<std::string, ObjectEntry> objects;
};

template<typename T>
inline void initializeReverseIndex(const std::vector<T> &v, std::unordered_map<T, int> &m)
{
    for (typename std::vector<T>::size_type i = 0; i < v.size(); i++) {
        m[v[i]] = i;
    }
}

std::filesystem::path getConfigPath(const std::string &moduleName)
{
    std::filesystem::path moduleDir(moduleName);
    return moduleDir / std::filesystem::path("game.json");
}

std::pair<std::string, std::string> parseClassName(const std::string &className)
{
    std::vector<std::string> tokens;
    boost::split(tokens, className, boost::is_any_of(":"));
    if (tokens.size() != 2) {
        throw std::runtime_error("invalid class name format");
    }
    return {tokens[0], tokens[1]};
}

GameConfig parseConfig(const std::filesystem::path &configPath)
{
    std::ifstream ifs(configPath);
    auto configJson = nlohmann::json::parse(ifs);

    auto config = GameConfig{
        .blueprint = configJson["blueprint"],
        .minPlayers = configJson["min_players"],
        .maxPlayers = configJson["max_players"],
        .moveLimit = configJson["move_limit"],
    };

    for (const auto& [name, entry] : configJson["objects"].items()) {
        auto [moduleName, className] = parseClassName(entry["class"]);
        config.objects[name] = {
            .moduleName = moduleName,
            .className = className,
            .templatePath = entry["template"]
        };
    }

    return config;
}

std::string readFile(const std::string &moduleDir, const std::string &path)
{
    std::filesystem::path moduleDirPath(moduleDir);
    auto fullPath = moduleDirPath / std::filesystem::path(path);

    std::stringstream ss;
    std::ifstream uiFile(fullPath);
    ss << uiFile.rdbuf();

    return ss.str();
}

std::shared_ptr<Spielbrett::OpenSpielGame> makeOpenSpielGame(
    const std::string &instanceType,
    const GameConfig &config,
    const Spielbrett::Board &board,
    int numPlayers)
{
    open_spiel::GameType::Information information;
    if (board.hasPrivateInformation()) {
        information = open_spiel::GameType::Information::kImperfectInformation;
    }
    else {
        information = open_spiel::GameType::Information::kPerfectInformation;
    }

    auto gameType = open_spiel::GameType{
        .short_name = instanceType,
        .long_name = instanceType,
        .dynamics = open_spiel::GameType::Dynamics::kSequential,
        .chance_mode = open_spiel::GameType::ChanceMode::kDeterministic,
        .information = information,
        .utility = open_spiel::GameType::Utility::kZeroSum,
        .reward_model = open_spiel::GameType::RewardModel::kTerminal,
        .max_num_players = config.maxPlayers,
        .min_num_players = config.minPlayers,
        .provides_information_state_string = false,
        .provides_information_state_tensor = false,
        .provides_observation_string = true,
        .provides_observation_tensor = true,
        .parameter_specification = {
            {"num_players", open_spiel::GameParameter(config.minPlayers)}}};

    auto gameInfo = open_spiel::GameInfo{
        .num_distinct_actions = board.numDistinctActions(),
        .max_chance_outcomes = 0,
        .num_players = numPlayers,
        .min_utility = -1.0,
        .max_utility = 1.0 * numPlayers,
        .utility_sum = 0.0,
        .max_game_length = config.moveLimit};

    auto params = open_spiel::GameParameters{
        {"num_players", open_spiel::GameParameter(numPlayers)}};

    return std::make_shared<Spielbrett::OpenSpielGame>(gameType, gameInfo, params);
}

} // namespace

namespace Spielbrett {

Instance::Instance(const std::string &instanceType, const std::vector<UserID> &userIds) :
    userIds(userIds)
{
    initializeReverseIndex(userIds, playerIndices);

    auto configPath = getConfigPath(instanceType);
    auto config = parseConfig(configPath);

    std::unordered_map<std::string, std::string> templates;
    for (auto &[name, entry] : config.objects) {
        runtime.loadClass(name, entry.moduleName, entry.className);
        auto templateStr = readFile(instanceType, entry.templatePath);
        templates.emplace(name, templateStr);
    }

    auto blueprintXml = readFile(instanceType, config.blueprint);
    board = std::make_unique<Board>(runtime, blueprintXml, templates);

    openSpielGame = makeOpenSpielGame(instanceType, config, *board, playerIndices.size());
}

void Instance::performAction(const std::string &userId, const Board::Action &action)
{
    std::unique_lock lock(sm);

    if (!playerIndices.contains(userId)) {
        std::stringstream ss;
        ss << "user " << userId << " is not participating in the game";
        throw std::invalid_argument(ss.str());
    }
    auto playerIndex = playerIndices.at(userId);

    board->performAction(playerIndex, action);
}

std::unordered_map<UserID, std::string> Instance::render() const
{
    std::shared_lock lock(sm);

    std::unordered_map<UserID, std::string> result;
    for (const auto &userId : userIds) {
        result[userId] = doRender(userId);
    }

    return result;
}

std::string Instance::render(const UserID &userId) const
{
    std::shared_lock lock(sm);

    if (!playerIndices.contains(userId)) {
        std::stringstream ss;
        ss << "user " << userId << " is not participating in the game";
        throw std::invalid_argument(ss.str());
    }

    return doRender(userId);
}

std::string Instance::doRender(const UserID &userId) const
{
    auto playerIndex = playerIndices.at(userId);

    return board->render(playerIndex);
}

}
