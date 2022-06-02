#ifndef TEAMSREPOSITORY_H
#define TEAMSREPOSITORY_H

#include <libpq-fe.h>
#include <vector>

#include "ITeamsRepository.h"
#include "EssensitiesDTO/TeamDTO.h"

class TeamsRepository : public ITeamsRepository
{
public:
    TeamsRepository();
    virtual ~TeamsRepository() = default;
    virtual shared_ptr<TeamBL> getTeam(int id) override;
    shared_ptr<vector<TeamDTO>> getTeamsByCaptainId(int captain_id);
    shared_ptr<vector<TeamDTO>> getTeamsByTournament(int tournament_id);
    shared_ptr<vector<TeamDTO>> getAllTeams();
    virtual void addTeam(TeamBL& team_bl) override;
    virtual void deleteTeam(int id) override;
    virtual void updateTeam(TeamBL& team_bl, int id) override;

protected:
    void connect();

    shared_ptr<PGconn> m_connection;
};

#endif // TEAMSREPOSITORY_H
