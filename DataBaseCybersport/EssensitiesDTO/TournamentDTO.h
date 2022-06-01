#ifndef TOURNAMENTDTO_H
#define TOURNAMENTDTO_H

#include <string>

using namespace std;

class TournamentDTO
{
public:
    TournamentDTO() = delete;
    TournamentDTO(int id, string country, string organizer, string name, int prize_pool);

    int &getId();
    string &getCountry();
    string &getOrganizer();
    string &getName();
    int &getPrizePool();

private:
    int id;
    string country, organizer, name;
    int prize_pool;
};

#endif // TOURNAMENTDTO_H
