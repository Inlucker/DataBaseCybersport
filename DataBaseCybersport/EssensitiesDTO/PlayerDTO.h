#ifndef PLAYERDTO_H
#define PLAYERDTO_H

#include <string>

using namespace std;

class PlayerDTO
{
public:
    PlayerDTO() = delete;
    PlayerDTO(int _id, string t, string c, string nick, string f_n, string s_n, int b_y, string m_r, int rat);

    int getId();
    string getTeam();
    string getCountry();
    string getNickname();
    string getFirstName();
    string getSecondName();
    int getBirthYear();
    string getMainRole();
    int getRating();

private:
    int id;
    string team, country;
    string nickname, first_name, second_name;
    int birth_year;
    string main_role;
    int rating;
};

#endif // PLAYERDTO_H
