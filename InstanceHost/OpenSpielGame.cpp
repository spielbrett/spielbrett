#include "OpenSpielGame.h"

#include <stdexcept>

OpenSpielState::OpenSpielState(std::shared_ptr<const open_spiel::Game> game) :
    open_spiel::State(game)
{
}

open_spiel::Player OpenSpielState::CurrentPlayer() const
{
    throw std::logic_error("not implemented");
}

std::vector<open_spiel::Action> OpenSpielState::LegalActions() const
{
    throw std::logic_error("not implemented");
}

bool OpenSpielState::IsTerminal() const
{
    throw std::logic_error("not implemented");
}

std::vector<double> OpenSpielState::Returns() const
{
    throw std::logic_error("not implemented");
}

std::string OpenSpielState::ActionToString(
    open_spiel::Player player,
    open_spiel::Action action_id) const
{
    throw std::logic_error("not implemented");
}

std::string OpenSpielState::ToString() const
{
    throw std::logic_error("not implemented");
}

std::unique_ptr<open_spiel::State> OpenSpielState::Clone() const
{
    throw std::logic_error("not implemented");
}

OpenSpielGame::OpenSpielGame(
    const open_spiel::GameType &gameType,
    const open_spiel::GameInfo &gameInfo,
    const open_spiel::GameParameters &params) :
    open_spiel::Game(gameType, params),
    gameInfo(gameInfo)
{
}

int OpenSpielGame::NumDistinctActions() const
{
    return gameInfo.num_distinct_actions;
}

int OpenSpielGame::MaxChanceOutcomes() const
{
    return gameInfo.max_chance_outcomes;
}

int OpenSpielGame::NumPlayers() const
{
    return gameInfo.num_players;
}

double OpenSpielGame::MinUtility() const
{
    return gameInfo.min_utility;
}

double OpenSpielGame::MaxUtility() const
{
    return gameInfo.max_utility;
}

absl::optional<double> OpenSpielGame::UtilitySum() const
{
    return gameInfo.utility_sum;
}

int OpenSpielGame::MaxGameLength() const
{
    return gameInfo.max_game_length;
}

std::unique_ptr<open_spiel::State> OpenSpielGame::NewInitialState() const
{
    return std::make_unique<OpenSpielState>(shared_from_this());
}
