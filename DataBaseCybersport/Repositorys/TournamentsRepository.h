#ifndef TOURNAMENTSREPOSITORY_H
#define TOURNAMENTSREPOSITORY_H

#include <libpq-fe.h>
#include <memory>
#include <vector>

using namespace std;

#include "EssensitiesDTO/TournamentDTO.h"

class TournamentsRepository
{
public:
    TournamentsRepository();

    shared_ptr<vector<TournamentDTO>> getTournamentsDTOByOrgId(int org_id);

protected:
    void connect();

    shared_ptr<PGconn> m_connection;
};

#endif // TOURNAMENTSREPOSITORY_H
