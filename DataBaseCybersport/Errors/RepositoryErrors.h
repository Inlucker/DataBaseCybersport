#ifndef REPOSITORYERRORS_H
#define REPOSITORYERRORS_H

#include "BaseError.h"

class ConnectionError : public BaseError
{
public:
    ConnectionError(string info, string filename, int line, const char *time, string error = "Connection error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class LoginError : public BaseError
{
public:
    LoginError(string info, string filename, int line, const char *time, string error = "Wrong username or password")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class GetUsersError : public BaseError
{
public:
    GetUsersError(string info, string filename, int line, const char *time, string error = "Get user error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class UpdateUserError : public BaseError
{
public:
    UpdateUserError(string info, string filename, int line, const char *time, string error = "Update user error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class RegistrateUserError : public BaseError
{
public:
    RegistrateUserError(string info, string filename, int line, const char *time, string error = "Registrate user error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class DeleteUserError : public BaseError
{
public:
    DeleteUserError(string info, string filename, int line, const char *time, string error = "Delete user error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class GetUserRoleError : public BaseError
{
public:
    GetUserRoleError(string info, string filename, int line, const char *time, string error = "Get user role error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class GetPlayerError : public BaseError
{
public:
    GetPlayerError(string info, string filename, int line, const char *time, string error = "Get player error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class InsertPlayerError : public BaseError
{
public:
    InsertPlayerError(string info, string filename, int line, const char *time, string error = "Insert player error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class UpdatePlayerError : public BaseError
{
public:
    UpdatePlayerError(string info, string filename, int line, const char *time, string error = "Update player error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class GetTeamError : public BaseError
{
public:
    GetTeamError(string info, string filename, int line, const char *time, string error = "Get team error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class GetCountryError : public BaseError
{
public:
    GetCountryError(string info, string filename, int line, const char *time, string error = "Get country error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

#endif // REPOSITORYERRORS_H
