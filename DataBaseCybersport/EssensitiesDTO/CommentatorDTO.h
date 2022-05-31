#ifndef COMMENTATORDTO_H
#define COMMENTATORDTO_H

#include <string>

using namespace std;

class CommentatorDTO
{
public:
    CommentatorDTO() = delete;
    CommentatorDTO(int id, string studio, string country, string nickname, string first_name, string second_name, int birth_year, int popularity);

    int &getId();
    string &getStudio();
    string &getCountry();
    string &getNickname();
    string &getFirstName();
    string &getSecondName();
    int &getBirthYear();
    int &getPopularity();

private:
    int id;
    string studio, country, nickname, first_name, second_name;
    int birth_year, popularity;
};

#endif // COMMENTATORDTO_H
