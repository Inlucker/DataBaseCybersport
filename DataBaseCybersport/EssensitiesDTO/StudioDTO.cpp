#include "StudioDTO.h"

/*StudioDTO::StudioDTO()
{

}*/

StudioDTO::StudioDTO(int id, string country, string owner, string name, int avg) :
    id(id), country(country), owner(owner), name(name), avg_popularity(avg)
{

}

int &StudioDTO::getId()
{
    return id;
}

string &StudioDTO::getCountry()
{
    return country;
}

string &StudioDTO::getOwner()
{
    return owner;
}

string &StudioDTO::getName()
{
    return name;
}

int &StudioDTO::getAvgPopularity()
{
    return avg_popularity;
}
