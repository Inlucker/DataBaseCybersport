#ifndef COMMENTATORBL_H
#define COMMENTATORBL_H

#include <string>

using namespace std;

class CommentatorBL
{
public:
    CommentatorBL() = delete;
    CommentatorBL(int id, int studio_id, int country_id, string nickname, string first_name, string second_name, int birth_year, int popularity);

    int &getId();
    int &getStudio();
    int &getCountry();
    string &getNickname();
    string &getFirstName();
    string &getSecondName();
    int &getBirthYear();
    int &getPopularity();

private:
    int id, studio_id, country_id;
    string nickname, first_name, second_name;
    int birth_year, popularity;
};

#endif // COMMENTATORBL_H
