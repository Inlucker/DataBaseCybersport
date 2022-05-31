#ifndef PLAYERBL_H
#define PLAYERBL_H

#include <string>

using namespace std;

class PlayerBL
{
public:
    PlayerBL() = delete;
    PlayerBL(int _id, int t_id, int c_id, string nick, string f_n, string s_n, int b_y, string m_r, int rat);

    int getId();
    int getTeamId();
    int getCountryId();
    string getNickname();
    string getFirstName();
    string getSecondName();
    int getBirthYear();
    string getMainRole();
    int getRating();

private:
    int id, team_id, country_id;
    string nickname, first_name, second_name;
    int birth_year;
    string main_role;
    int rating;
};

#endif // PLAYERBL_H
