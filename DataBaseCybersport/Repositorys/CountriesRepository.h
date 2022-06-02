#ifndef COUNTRIESREPOSITORY_H
#define COUNTRIESREPOSITORY_H

#include <libpq-fe.h>
#include <memory>
#include <vector>

using namespace std;

#include "Repositorys/ICountriesRepository.h"

class CountriesRepository : public ICountriesRepository
{
public:
    CountriesRepository();
    virtual ~CountriesRepository() = default;

    virtual string getCountry(int id) override;
    shared_ptr<vector<string>> getAllCountries();

protected:
    void connect();

    shared_ptr<PGconn> m_connection;
};

#endif // COUNTRIESREPOSITORY_H
