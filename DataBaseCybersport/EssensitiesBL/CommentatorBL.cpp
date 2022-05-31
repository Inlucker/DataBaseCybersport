#include "CommentatorBL.h"

/*CommentatorBL::CommentatorBL()
{

}*/

CommentatorBL::CommentatorBL(int id, int studio_id, int country_id, string nickname, string first_name, string second_name, int birth_year, int popularity) :
    id(id), studio_id(studio_id), country_id(country_id), nickname(nickname), first_name(first_name), second_name(second_name), birth_year(birth_year), popularity(popularity)
{

}

int &CommentatorBL::getId()
{
    return id;
}

int &CommentatorBL::getStudio()
{
    return studio_id;
}

int &CommentatorBL::getCountry()
{
    return country_id;
}

string &CommentatorBL::getNickname()
{
    return nickname;
}

string &CommentatorBL::getFirstName()
{
    return first_name;
}

string &CommentatorBL::getSecondName()
{
    return second_name;
}

int &CommentatorBL::getBirthYear()
{
    return birth_year;
}

int &CommentatorBL::getPopularity()
{
    return popularity;
}
