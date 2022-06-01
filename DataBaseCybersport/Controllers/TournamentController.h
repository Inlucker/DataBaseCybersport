#ifndef TOURNAMENTCONTROLLER_H
#define TOURNAMENTCONTROLLER_H

#include "BaseController.h"

class TournamentController : public BaseController
{
public:
    TournamentController();

    void setCurTournamentId(int id);
    int getCurTournamentId() const;

private:
    int cur_tournament_id = -1;
};

#endif // TOURNAMENTCONTROLLER_H
