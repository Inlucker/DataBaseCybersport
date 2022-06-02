#ifndef TOURNAMENTBL_H
#define TOURNAMENTBL_H

#include <string>

using namespace std;

class TournamentBL
{
public:
    TournamentBL() = delete;
    TournamentBL(int id, int c_id, int o_id, string name, int p_p);

    int &getId();
    int &getCountryId();
    int &getOrganizerId();
    string &getName();
    int &getPrizePool();

private:
    int id, country_id, organizer_id;
    string name;
    int prize_pool;
};

#endif // TOURNAMENTBL_H
