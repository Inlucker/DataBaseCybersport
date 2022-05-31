#ifndef ICOUNTRIESREPOSITORY_H
#define ICOUNTRIESREPOSITORY_H

#include <string>

using namespace std;

class ICountriesRepository
{
public:
    ICountriesRepository();
    virtual ~ICountriesRepository() = 0;

    virtual string getCountry(int id) = 0;
};

#endif // ICOUNTRIESREPOSITORY_H
