#include "TournamentDTO.h"

TournamentDTO::TournamentDTO(int id, string country, string organizer, string name, int prize_pool) :
    id(id), country(country), organizer(organizer), name(name), prize_pool(prize_pool)
{

}

int &TournamentDTO::getId()
{
    return id;
}

string &TournamentDTO::getCountry()
{
    return country;
}

string &TournamentDTO::getOrganizer()
{
    return organizer;
}

string &TournamentDTO::getName()
{
    return name;
}

int &TournamentDTO::getPrizePool()
{
    return prize_pool;
}
