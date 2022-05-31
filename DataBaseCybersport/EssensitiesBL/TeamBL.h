#ifndef TEAMBL_H
#define TEAMBL_H

#include <string>

using namespace std;

class TeamBL
{
public:
    TeamBL() = delete;
    TeamBL(int i, int c_id, int s_id, int cap_id, string n);

    int getId();
    int getCountryId();
    int getSponsorId();
    int getCaptainId();
    string getName();

private:
    int id, country_id, sponsor_id, captain_id;
    string name;
};

#endif // TEAMBL_H
