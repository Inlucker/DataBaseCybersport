#ifndef IPLAYERSREPOSITORY_H
#define IPLAYERSREPOSITORY_H

#include <memory>

using namespace std;

#include "EssensitiesBL/PlayerBL.h"

class IPlayersRepository
{
public:
    IPlayersRepository();
    virtual ~IPlayersRepository() = 0;
    virtual shared_ptr<PlayerBL> getPlayer(int id) = 0;
    virtual void addPlayer(PlayerBL& user_bl) = 0;
    virtual void deletePlayer(int id) = 0;
    virtual void updatePlayer(PlayerBL& user_bl, int id) = 0;
};

#endif // IPLAYERSREPOSITORY_H
