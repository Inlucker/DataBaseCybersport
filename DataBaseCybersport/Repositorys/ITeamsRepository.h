#ifndef ITEAMSREPOSITORY_H
#define ITEAMSREPOSITORY_H

#include <memory>

using namespace std;

#include "EssensitiesBL/TeamBL.h"

class ITeamsRepository
{
public:
    ITeamsRepository();
    virtual ~ITeamsRepository() = 0;
    virtual shared_ptr<TeamBL> getTeam(int id) = 0;
    virtual void addTeam(TeamBL& user_bl) = 0;
    virtual void deleteTeam(int id) = 0;
    virtual void updateTeam(TeamBL& user_bl, int id) = 0;
};

#endif // ITEAMSREPOSITORY_H
