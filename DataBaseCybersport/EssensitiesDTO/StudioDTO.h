#ifndef STUDIODTO_H
#define STUDIODTO_H

#include <string>

using namespace std;

class StudioDTO
{
public:
    StudioDTO() = delete;
    StudioDTO(int id, string country, string owner, string name, int avg);

    int &getId();
    string &getCountry();
    string &getOwner();
    string &getName();
    int &getAvgPopularity();
private:
    int id;
    string country, owner, name;
    int avg_popularity;
};

#endif // STUDIODTO_H
