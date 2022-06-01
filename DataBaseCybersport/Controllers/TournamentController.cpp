#include "TournamentController.h"

TournamentController::TournamentController()
{

}

void TournamentController::setCurTournamentId(int id)
{
    cur_tournament_id = id;
}

int TournamentController::getCurTournamentId() const
{
    return cur_tournament_id;
}
