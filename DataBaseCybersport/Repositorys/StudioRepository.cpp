#include "StudioRepository.h"
#include "Errors/RepositoryErrors.h"
#include "Settings.h"

StudioRepository::StudioRepository()
{

}

shared_ptr<vector<StudioDTO> > StudioRepository::getStudiosDTOByOwnerId(int owner_id)
{
    connect();
    string query = "select * FROM studios_view where owner_id =" + to_string(owner_id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<StudioDTO>> vec = make_shared<vector<StudioDTO>>();
    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        int rows_n = PQntuples(res);
        if (PQresultStatus(res) == PGRES_TUPLES_OK && rows_n)
        {
            for (int i = 0; i < rows_n; i++)
            {
                int ID = atoi(PQgetvalue (res, i, 0));
                string country = PQgetvalue (res, i, 1);
                string owner = PQgetvalue (res, i, 2);
                string name = PQgetvalue (res, i, 3);
                int avg_poularity = atoi(PQgetvalue (res, i, 4));

                vec->push_back(StudioDTO(ID, country, owner, name, avg_poularity));
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
        throw GetStudioError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

void StudioRepository::connect()
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
