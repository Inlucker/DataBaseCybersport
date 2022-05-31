#ifndef COUNTRIESREPOSITORY_H
#define COUNTRIESREPOSITORY_H

#include <libpq-fe.h>
#include <memory>

#include "Repositorys/ICountriesRepository.h"

class CountriesRepository : public ICountriesRepository
{
public:
    CountriesRepository();
    virtual ~CountriesRepository() = default;

    virtual string getCountry(int id) override;

protected:
    void connect();

    shared_ptr<PGconn> m_connection;
};

#endif // COUNTRIESREPOSITORY_H
