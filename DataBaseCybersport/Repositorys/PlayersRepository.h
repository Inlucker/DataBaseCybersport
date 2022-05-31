#ifndef PLAYERSREPOSITORY_H
#define PLAYERSREPOSITORY_H

#include <libpq-fe.h>
#include <vector>

#include "IPlayersRepository.h"

class PlayersRepository : public IPlayersRepository
{
public:
    PlayersRepository();
    virtual ~PlayersRepository() = default;
    virtual shared_ptr<PlayerBL> getPlayer(int id) override;
    shared_ptr<vector<PlayerBL> > getFreePlayers();
    virtual void addPlayer(PlayerBL& player_bl) override;
    virtual void deletePlayer(int id) override;
    virtual void updatePlayer(PlayerBL& player_bl, int id) override;

protected:
    void connect();

    shared_ptr<PGconn> m_connection;
};

#endif // PLAYERSREPOSITORY_H
