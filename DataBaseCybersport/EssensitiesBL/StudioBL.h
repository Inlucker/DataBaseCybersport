#ifndef STUDIOBL_H
#define STUDIOBL_H

#include <string>

using namespace std;

class StudioBL
{
public:
    StudioBL() = delete;
    StudioBL(int id, int country, int owner, string name);

    int &getId();
    int &getCountryId();
    int &getOwnerId();
    string &getName();
private:
    int id;
    int country_id, owner_id;
    string name;
};

#endif // STUDIOBL_H
