#ifndef MATCHBL_H
#define MATCHBL_H

#include <string>

using namespace std;

class MatchBL
{
public:
    MatchBL() = delete;
    MatchBL(int id, int t1, int t2, int w, int s, int c, int t, string d);

    int &getId();
    int &getTeam1Id();
    int &getTeam2Id();
    int &getWinnerId();
    int &getStudioId();
    int &getCommentatorId();
    int &getTournamentId();
    string &getDate();
private:
    int id, team1_id, team2_id, winner_id, studio_id, commentator_id, tournament_id;
    string date;
};

#endif // MATCHBL_H
