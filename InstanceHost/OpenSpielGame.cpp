#include "OpenSpielGame.h"
#include "open_spiel/spiel_globals.h"
#include "open_spiel/spiel_utils.h"

#include <memory>
#include <stdexcept>
#include <string>

namespace Spielbrett {

OpenSpielState::OpenSpielState(std::shared_ptr<const open_spiel::Game> game, std::shared_ptr<Spielbrett::Board> board) :
    open_spiel::State(game), board(board)
{
}

open_spiel::Player OpenSpielState::CurrentPlayer() const
{
    for (int i = 0; i < game->NumPlayers(); i++) {
        if (!board->render(i).second.empty()) {
            return i;
        }
    }
    return open_spiel::kTerminalPlayerId;
}

std::vector<open_spiel::Action> OpenSpielState::LegalActions() const
{
    std::vector<open_spiel::Action> legalActions;
    for (int i = 0; i < game->NumPlayers(); i++) {
        auto [renderStr, actions] = board->render(i);
        if (!actions.empty()) {
            for (const auto &action : actions) {
                legalActions.push_back(board->getActionIndex(action));
            }
            break;
        }
    }
    return legalActions;
}

bool OpenSpielState::IsTerminal() const
{
    for (int i = 0; i < game->NumPlayers(); i++) {
        if (!board->render(i).second.empty()) {
            return false;
        }
    }
    return true;
}

std::vector<double> OpenSpielState::Returns() const
{
    std::vector<double> returns;
    for (int i = 0; i < game->NumPlayers(); i++) {
        returns.push_back(board->score(i));
    }
    return returns;
}

std::string OpenSpielState::ActionToString(
    open_spiel::Player player,
    open_spiel::Action action_id) const
{
    return std::to_string(action_id);
}

std::string OpenSpielState::ToString() const
{
    std::string result;
    for (int i = 0; i < game->NumPlayers(); i++) {
        result += "Player " + std::to_string(i) + " board:\n";
        result += board->render(i).first + "\n\n";
    }
    return result;
}

std::unique_ptr<open_spiel::State> OpenSpielState::Clone() const
{
    return std::make_unique<OpenSpielState>(game, board->clone());
}

OpenSpielGame::OpenSpielGame(
    const open_spiel::GameType &gameType,
    const open_spiel::GameInfo &gameInfo,
    const open_spiel::GameParameters &params,
    std::shared_ptr<Spielbrett::Board> board) :
    open_spiel::Game(gameType, params),
    gameInfo(gameInfo),
    board(board)
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
    return std::make_unique<OpenSpielState>(shared_from_this(), board->clone());
}

}
