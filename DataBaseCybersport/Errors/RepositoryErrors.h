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

class InsertTeamError : public BaseError
{
public:
    InsertTeamError(string info, string filename, int line, const char *time, string error = "Insert team error")
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

class GetCommentatorError : public BaseError
{
public:
    GetCommentatorError(string info, string filename, int line, const char *time, string error = "Get commentator error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class UpdateCommentatorError : public BaseError
{
public:
    UpdateCommentatorError(string info, string filename, int line, const char *time, string error = "Update commentator error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class GetTournamentError : public BaseError
{
public:
    GetTournamentError(string info, string filename, int line, const char *time, string error = "Get tournament error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class InsertTournamentError : public BaseError
{
public:
    InsertTournamentError(string info, string filename, int line, const char *time, string error = "Insert tournament error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class GetStudioError : public BaseError
{
public:
    GetStudioError(string info, string filename, int line, const char *time, string error = "Get studio error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class GetMatchError : public BaseError
{
public:
    GetMatchError(string info, string filename, int line, const char *time, string error = "Get match error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class InsertMatchError : public BaseError
{
public:
    InsertMatchError(string info, string filename, int line, const char *time, string error = "Insert match error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class UpdateMatchError : public BaseError
{
public:
    UpdateMatchError(string info, string filename, int line, const char *time, string error = "Update match error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class GetSponsorError : public BaseError
{
public:
    GetSponsorError(string info, string filename, int line, const char *time, string error = "Get sponsor error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

#endif // REPOSITORYERRORS_H
