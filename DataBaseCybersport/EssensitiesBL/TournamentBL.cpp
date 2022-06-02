#include "TournamentBL.h"

TournamentBL::TournamentBL(int id, int c_id, int o_id, string name, int p_p) :
    id(id), country_id(c_id), organizer_id(o_id), name(name), prize_pool(p_p)
{

}

int &TournamentBL::getId()
{
    return id;
}

int &TournamentBL::getCountryId()
{
    return country_id;
}

int &TournamentBL::getOrganizerId()
{
    return organizer_id;
}

string &TournamentBL::getName()
{
    return name;
}

int &TournamentBL::getPrizePool()
{
    return prize_pool;
}
