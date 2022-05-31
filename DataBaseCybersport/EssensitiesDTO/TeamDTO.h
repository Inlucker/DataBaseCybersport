#ifndef TEAMDTO_H
#define TEAMDTO_H

#include <string>

using namespace std;

class TeamDTO
{
public:
    TeamDTO();
    TeamDTO(int i, string coun, string s, string cap, string n, int avg);

    int getId();
    string getCountry();
    string getSponsor();
    string getCaptain();
    string getName();
    int getAvgRating();

private:
    int id;
    string country, sponsor, captain, name;
    int avg_rating;
};

#endif // TEAMDTO_H
