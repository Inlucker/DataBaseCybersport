#include "StudioBL.h"

StudioBL::StudioBL(int id, int country, int owner, string name) :
    id(id), country_id(country), owner_id(owner), name(name)
{

}

int &StudioBL::getId()
{
    return id;
}

int &StudioBL::getCountryId()
{
    return country_id;
}

int &StudioBL::getOwnerId()
{
    return owner_id;
}

string &StudioBL::getName()
{
    return name;
}
