#include "TeamBL.h"

/*TeamBL::TeamBL()
{

}*/

TeamBL::TeamBL(int i, int c_id, int s_id, int cap_id, string n) :
    id(i), country_id(c_id), sponsor_id(s_id), captain_id(cap_id), name(n)
{

}

int TeamBL::getId()
{
    return id;
}

int TeamBL::getCountryId()
{
    return country_id;
}

int TeamBL::getSponsorId()
{
    return sponsor_id;
}

int TeamBL::getCaptainId()
{
    return captain_id;
}

string TeamBL::getName()
{
    return name;
}
