#ifndef MATCHESREPOSITORY_H
#define MATCHESREPOSITORY_H

#include <libpq-fe.h>
#include <vector>
#include <memory>

using namespace std;

#include "EssensitiesDTO/MatchDTO.h"
#include "EssensitiesBL/MatchBL.h"

class MatchesRepository
{
public:
    MatchesRepository();

    shared_ptr<vector<MatchDTO>> getMatchesDTOByTournament(int tournament_id);
    shared_ptr<MatchBL> getMatch(int match_id);
    void addMatch(MatchBL& match);

protected:
    void connect();

    shared_ptr<PGconn> m_connection;
};

#endif // MATCHESREPOSITORY_H
