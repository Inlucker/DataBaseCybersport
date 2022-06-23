#ifndef SPONSORSREPOSITORY_H
#define SPONSORSREPOSITORY_H

#include <libpq-fe.h>
#include <memory>
#include <vector>

using namespace std;

class SponsorsRepository
{
public:
    SponsorsRepository();
    ~SponsorsRepository() = default;

    shared_ptr<vector<string>> getAllSponsors();

protected:
    void connect();

    shared_ptr<PGconn> m_connection;
};

#endif // SPONSORSREPOSITORY_H
