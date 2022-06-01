#ifndef MATCHDTO_H
#define MATCHDTO_H

#include <string>

using namespace std;

class MatchDTO
{
public:
    MatchDTO() = delete;
    MatchDTO(int id, string t1, string t2, string w, string s, string c, string t, string d);
    //MatchDTO(string t1, string t2, string w, string s, string c, string t, string d);

    int &getId();
    string &getTeam1();
    string &getTeam2();
    string &getWinner();
    string &getStudio();
    string &getCommentator();
    string &getTournament();
    string &getDate();
private:
    int id;
    string team1, team2, winner, studio, commentator, tournament, date;
};

#endif // MATCHDTO_H
