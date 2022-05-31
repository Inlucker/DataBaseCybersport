#ifndef USERROLESREPOSITORY_H
#define USERROLESREPOSITORY_H

#include <libpq-fe.h>
#include <memory>

#include "Repositorys/IUserRolesRepository.h"

class UserRolesRepository : public IUserRolesRepository
{
public:
    UserRolesRepository();
    virtual ~UserRolesRepository() = default;

    virtual string getUserRole(int id) override;

protected:
    void connect();

    shared_ptr<PGconn> m_connection;
};

#endif // USERROLESREPOSITORY_H
