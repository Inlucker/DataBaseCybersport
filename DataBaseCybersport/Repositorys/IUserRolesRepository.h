#ifndef IUSERROLESREPOSITORY_H
#define IUSERROLESREPOSITORY_H

#include <memory>

using namespace std;

class IUserRolesRepository
{
public:
    IUserRolesRepository();
    virtual ~IUserRolesRepository() = 0;

    virtual string getUserRole(int id) = 0;
    //virtual void addUser(UserBL& user_bl) = 0;
    //virtual void deleteUser(int id) = 0;
    //virtual void updateUser(UserBL& user_bl, int id) = 0;
};

#endif // IUSERROLESREPOSITORY_H
