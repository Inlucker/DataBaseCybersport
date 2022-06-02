#include "CountriesRepository.h"
#include "Errors/RepositoryErrors.h"
#include "Settings.h"

CountriesRepository::CountriesRepository()
{

}

string CountriesRepository::getCountry(int id)
{
    connect();
    string query = "select name from Countries where id='" + std::to_string(id) + "';";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            string role_name = PQgetvalue (res, 0, 0);

            return role_name;
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
        throw GetCountryError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else
        throw GetCountryError("Unexpected getCountry error", __FILE__, __LINE__, ctime(&t_time));
}

shared_ptr<vector<string> > CountriesRepository::getAllCountries()
{
    connect();
    string query = "select name FROM countries;";
    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<string>> vec = make_shared<vector<string>>();
    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        int rows_n = PQntuples(res);
        if (PQresultStatus(res) == PGRES_TUPLES_OK && rows_n)
        {
            for (int i = 0; i < rows_n; i++)
            {
                string country_name = PQgetvalue (res, i, 0);

                vec->push_back(country_name);
            }
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
        throw GetCountryError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

void CountriesRepository::connect()
{
    string m_dbhost = Settings::get(Settings::DBHost, Settings::DataBase).toString().toStdString();
    int m_dbport = Settings::get(Settings::DBPort, Settings::DataBase).toInt();
    string m_dbname = Settings::get(Settings::DBName, Settings::DataBase).toString().toStdString();
    string m_dbuser = Settings::get(Settings::DBUser, Settings::DataBase).toString().toStdString();
    string m_dbpass = Settings::get(Settings::DBPass, Settings::DataBase).toString().toStdString();

    m_connection.reset( PQsetdbLogin(m_dbhost.c_str(), to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
    {
       string err_msg = string (PQerrorMessage(m_connection.get()));
       time_t t_time = time(NULL);
       throw ConnectionError(err_msg, __FILE__, __LINE__, ctime(&t_time));
    }
}
