#ifndef TOURNAMENTSREPOSITORY_H
#define TOURNAMENTSREPOSITORY_H

#include <libpq-fe.h>
#include <memory>
#include <vector>

using namespace std;

#include "EssensitiesDTO/TournamentDTO.h"
#include "EssensitiesBL/TournamentBL.h"

class TournamentsRepository
{
public:
    TournamentsRepository();

    shared_ptr<vector<TournamentDTO>> getTournamentsDTOByOrgId(int org_id);
    int addTournament(TournamentBL &tournament_bl);
    void addTournamentTeams(int tournament_id, shared_ptr<vector<int>> teams_id);

protected:
    void connect();

    shared_ptr<PGconn> m_connection;
};

#endif // TOURNAMENTSREPOSITORY_H
