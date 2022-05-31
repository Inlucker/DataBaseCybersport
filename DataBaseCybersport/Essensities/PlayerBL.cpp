#include "PlayerBL.h"

/*PlayerBL::PlayerBL()
{

}*/

PlayerBL::PlayerBL(int _id, int t_id, int c_id, string nick, string f_n, string s_n, int b_y, string m_r, int rat) :
    id(_id), team_id(t_id), country_id(c_id), nickname(nick), first_name(f_n), second_name(s_n), birth_year(b_y), main_role(m_r), rating(rat)
{

}

int PlayerBL::getId()
{
    return id;
}

int PlayerBL::getTeamId()
{
    return team_id;
}

int PlayerBL::getCountryId()
{
    return country_id;
}

string PlayerBL::getNickname()
{
    return nickname;
}

string PlayerBL::getFirstName()
{
    return first_name;
}

string PlayerBL::getSecondName()
{
    return second_name;
}

int PlayerBL::getBirthYear()
{
    return birth_year;
}

string PlayerBL::getMainRole()
{
    return main_role;
}

int PlayerBL::getRating()
{
    return rating;
}
