#ifndef USERBL_H
#define USERBL_H

#include <string>

using namespace std;

class UserBL
{
public:
    UserBL();
    UserBL(int id, int r_id, string l, string p, bool del);

    bool operator ==(UserBL& an_ubl);
    bool operator !=(UserBL& an_ubl);

    int getId();
    const int& getRoleId() const;
    const string& getLogin() const;
    const string& getPassword() const;
    const bool &getDeleted() const;

private:
    int id = -1;
    int role_id = -1;
    string login = "";
    string password = "";
    bool deleted = false;
};

#endif // USERBL_H
