#include "TeamDTO.h"

TeamDTO::TeamDTO()
{

}

TeamDTO::TeamDTO(int i, string coun, string s, string cap, string n, int avg) :
    id(i), country(coun), sponsor(s), captain(cap), name(n), avg_rating(avg)
{

}

int TeamDTO::getId()
{
    return id;
}

string TeamDTO::getCountry()
{
    return country;
}

string TeamDTO::getSponsor()
{
    return sponsor;
}

string TeamDTO::getCaptain()
{
    return captain;
}

string TeamDTO::getName()
{
    return name;
}

int TeamDTO::getAvgRating()
{
    return avg_rating;
}
