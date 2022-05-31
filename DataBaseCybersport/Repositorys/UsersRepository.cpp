#include "UsersRepository.h"
#include "Errors/RepositoryErrors.h"
#include "Settings.h"

UsersRepository::UsersRepository()
{

}

shared_ptr<UserBL> UsersRepository::getUser(string login, string password)
{
    connect();
    string query = "select * from Users where login='" + login + "' and password = '" + password + "';";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue (res, 0, 0));
            int role_id = atoi(PQgetvalue (res, 0, 1));
            string login = PQgetvalue (res, 0, 2);
            string password = PQgetvalue (res, 0, 3);

            return make_shared<UserBL>(ID, role_id, password, login);
        }
        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = true;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag)
        throw LoginError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else
        throw LoginError("login or password", __FILE__, __LINE__, ctime(&t_time));
}

shared_ptr<UserBL> UsersRepository::getUserByLogin(string name)
{
    connect();
    string query = "select * from Users where login='" + name + "';";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue (res, 0, 0));
            int role_id = atoi(PQgetvalue (res, 0, 1));
            string login = PQgetvalue (res, 0, 2);
            string password = PQgetvalue (res, 0, 3);

            return make_shared<UserBL>(ID, role_id, password, login);
        }
        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = true;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag)
        throw GetUsersError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else
        throw GetUsersError("getUserByLogin", __FILE__, __LINE__, ctime(&t_time));
}

void UsersRepository::addUser(UserBL &user)
{
    connect();
    int role_id = user.getRoleId();
    string login = user.getLogin();
    string password = user.getPassword();

    string query = "insert into Users(role_id, login, password) values(";
    query += std::to_string(role_id) + ", '";
    query += login + "', '";
    query += password + "');";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = true;
        }

        PQclear( res );
    }

    if (flag)
    {
        time_t t_time = time(NULL);
        throw RegistrateUserError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    }
}

void UsersRepository::deleteUser(int id)
{
    connect();
    string query = "delete from Users where id=" + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    int flag = 0;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQcmdTuples(res)[0] == '0')
            flag = true;
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = 2;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag == 1)
        throw DeleteUserError("No such user", __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 2)
        throw DeleteUserError(error_msg, __FILE__, __LINE__, ctime(&t_time));
}

void UsersRepository::updateUser(UserBL &user_bl, int id)
{
    connect();
    //string query = "update login FROM PPO.Users where id = " + std::to_string(id) + ";";

    string login, password;
    int role_id = user_bl.getRoleId();
    login = user_bl.getLogin();
    password = user_bl.getPassword();

    string query = "update Users set login = '" + login;
    query += "', password = '" + password;
    query += "', role_id = " + std::to_string(role_id);
    query += " where id = " + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    int flag = 0;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQcmdTuples(res)[0] == '0')
            flag = 1;
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = 2;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag == 1)
        throw UpdateUserError("No such user", __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 2)
        throw UpdateUserError(error_msg, __FILE__, __LINE__, ctime(&t_time));
}

void UsersRepository::connect()
{
    string m_dbhost = Settings::get(Settings::DBHost, Settings::DataBase).toString().toStdString();
    int m_dbport = Settings::get(Settings::DBPort, Settings::DataBase).toInt();
    string m_dbname = Settings::get(Settings::DBName, Settings::DataBase).toString().toStdString();
    string m_dbuser = Settings::get(Settings::DBUser, Settings::DataBase).toString().toStdString();
    string m_dbpass = Settings::get(Settings::DBPass, Settings::DataBase).toString().toStdString();
    //m_schema = Settings::get(Settings::Schema, Settings::DataBase).toString().toStdString();

    m_connection.reset( PQsetdbLogin(m_dbhost.c_str(), to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
    {
       time_t t_time = time(NULL);
       throw ConnectionError("m_connection", __FILE__, __LINE__, ctime(&t_time));
    }
}
