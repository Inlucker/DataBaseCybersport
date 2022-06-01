#include "MatchDTO.h"

MatchDTO::MatchDTO(int id, string t1, string t2, string w, string s, string c, string t, string d) :
    id(id), team1(t1), team2(t2), winner(w), studio(s), commentator(c), tournament(t), date(d)
{

}

/*MatchDTO::MatchDTO(string t1, string t2, string w, string s, string c, string t, string d) :
    team1(t1), team2(t2), winner(w), studio(s), commentator(c), tournament(t), date(d)
{

}*/

int &MatchDTO::getId()
{
    return id;
}

string &MatchDTO::getTeam1()
{
    return team1;
}

string &MatchDTO::getTeam2()
{
    return team2;
}

string &MatchDTO::getWinner()
{
    return winner;
}

string &MatchDTO::getStudio()
{
    return studio;
}

string &MatchDTO::getCommentator()
{
    return commentator;
}

string &MatchDTO::getTournament()
{
    return tournament;
}

string &MatchDTO::getDate()
{
    return date;
}
