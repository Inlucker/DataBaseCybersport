#include "UserBL.h"

/*UserBL::UserBL()
{
    id = -1;
    role = "";
    login = "";
    password = "";
}*/

UserBL::UserBL(int i, int r_id, string l, string p) : id(i), role_id(r_id), login(l), password(p)
{
    id = i;
    role_id = r_id;
    login = l;
    password = p;
}

bool UserBL::operator ==(UserBL &an_ubl)
{
    bool res = true;

    if (this->id != an_ubl.id ||
            this->login != an_ubl.login ||
            this->password != an_ubl.password ||
            this->role_id != an_ubl.role_id)
        res = false;
    return res;
}

bool UserBL::operator !=(UserBL &an_ubl)
{
    return !(*this == an_ubl);
}

int UserBL::getId()
{
    return id;
}

const int &UserBL::getRoleId() const
{
    return role_id;
}

const string& UserBL::getLogin() const
{
    return login;
}

const string& UserBL::getPassword() const
{
    return password;
}
