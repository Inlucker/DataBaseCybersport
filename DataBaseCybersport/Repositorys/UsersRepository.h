#ifndef USERSREPOSITORY_H
#define USERSREPOSITORY_H

#include <iostream>
#include <libpq-fe.h>

using namespace std;

#include "IUsersRepository.h"
#include "Errors/RepositoryErrors.h"

class UsersRepository : public IUsersRepository
{
public:
    UsersRepository();
    virtual ~UsersRepository() = default;

    virtual shared_ptr<UserBL> getUser(string login, string password) override;
    shared_ptr<UserBL> getUserByLogin(string name);
    virtual void addUser(UserBL& user) override;
    virtual void deleteUser(int id) override;
    virtual void updateUser(UserBL& user_bl, int id) override;

protected:
    void connect();

    /*string m_dbhost;
    int m_dbport;
    string m_dbname;
    string m_dbuser;
    string m_dbpass;*/
    string m_schema;

    shared_ptr<PGconn> m_connection;
};

#endif // USERSREPOSITORY_H
