#include "MatchBL.h"

MatchBL::MatchBL(int t1, int t2, int w, int s, int c, int t, string d) :
    team1_id(t1), team2_id(t2), winner_id(w), studio_id(s), commentator_id(c), tournament_id(t), date(d)
{

}

int &MatchBL::getTeam1Id()
{
    return team1_id;
}

int &MatchBL::getTeam2Id()
{
    return team2_id;
}

int &MatchBL::getWinnerId()
{
    return winner_id;
}

int &MatchBL::getStudioId()
{
    return studio_id;
}

int &MatchBL::getCommentatorId()
{
    return commentator_id;
}

int &MatchBL::getTournamentId()
{
    return tournament_id;
}

string &MatchBL::getDate()
{
    return date;
}
