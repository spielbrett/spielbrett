#ifndef OPEN_SPIEL_GAME
#define OPEN_SPIEL_GAME

#include <open_spiel/spiel.h>

#include <memory>

class OpenSpielState : public open_spiel::State
{
public:
    OpenSpielState(std::shared_ptr<const open_spiel::Game> game);

    open_spiel::Player CurrentPlayer() const override;
    std::vector<open_spiel::Action> LegalActions() const override;
    bool IsTerminal() const override;
    std::vector<double> Returns() const override;

    std::string ActionToString(
        open_spiel::Player player,
        open_spiel::Action action_id) const override;
    std::string ToString() const override;

    std::unique_ptr<open_spiel::State> Clone() const override;
};

class OpenSpielGame : public open_spiel::Game
{
public:
    OpenSpielGame(
        const open_spiel::GameType &gameType,
        const open_spiel::GameInfo &gameInfo,
        const open_spiel::GameParameters &params);

    int NumDistinctActions() const override;
    int MaxChanceOutcomes() const override;
    int NumPlayers() const override;
    double MinUtility() const override;
    double MaxUtility() const override;
    double UtilitySum() const override;
    int MaxGameLength() const override;

    std::unique_ptr<open_spiel::State> NewInitialState() const override;

private:
    open_spiel::GameInfo gameInfo;
};

#endif // OPEN_SPIEL_GAME
