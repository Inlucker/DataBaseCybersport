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
    void addTournament(TournamentBL &tournament_nl);

protected:
    void connect();

    shared_ptr<PGconn> m_connection;
};

#endif // TOURNAMENTSREPOSITORY_H
