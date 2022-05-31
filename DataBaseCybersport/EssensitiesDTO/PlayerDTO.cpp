#include "PlayerDTO.h"

/*PlayersDTO::PlayersDTO()
{

}*/

PlayerDTO::PlayerDTO(int _id, string t, string c, string nick, string f_n, string s_n, int b_y, string m_r, int rat) :
    id(_id), team(t), country(c), nickname(nick), first_name(f_n), second_name(s_n), birth_year(b_y), main_role(m_r), rating(rat)
{

}

int PlayerDTO::getId()
{
    return id;
}

string PlayerDTO::getTeam()
{
    return team;
}

string PlayerDTO::getCountry()
{
    return country;
}

string PlayerDTO::getNickname()
{
    return nickname;
}

string PlayerDTO::getFirstName()
{
    return first_name;
}

string PlayerDTO::getSecondName()
{
    return second_name;
}

int PlayerDTO::getBirthYear()
{
    return birth_year;
}

string PlayerDTO::getMainRole()
{
    return main_role;
}

int PlayerDTO::getRating()
{
    return rating;
}
