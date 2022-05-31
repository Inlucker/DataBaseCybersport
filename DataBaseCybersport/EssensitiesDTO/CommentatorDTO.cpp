#include "CommentatorDTO.h"

/*CommentatorDTO::CommentatorDTO()
{

}*/

CommentatorDTO::CommentatorDTO(int id, string studio, string country, string nickname, string first_name, string second_name, int birth_year, int popularity) :
    id(id), studio(studio), country(country), nickname(nickname), first_name(first_name), second_name(second_name), birth_year(birth_year), popularity(popularity)
{

}

int &CommentatorDTO::getId()
{
    return id;
}

string &CommentatorDTO::getStudio()
{
    return studio;
}

string &CommentatorDTO::getCountry()
{
    return country;
}

string &CommentatorDTO::getNickname()
{
    return nickname;
}

string &CommentatorDTO::getFirstName()
{
    return first_name;
}

string &CommentatorDTO::getSecondName()
{
    return second_name;
}

int &CommentatorDTO::getBirthYear()
{
    return birth_year;
}

int &CommentatorDTO::getPopularity()
{
    return popularity;
}
