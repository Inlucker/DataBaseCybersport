#include "TeamsRepository.h"
#include "Errors/RepositoryErrors.h"
#include "Settings.h"

TeamsRepository::TeamsRepository()
{

}

shared_ptr<TeamBL> TeamsRepository::getTeam(int id)
{
    connect();
    string query = "select * from Teams where id='" + to_string(id) + "';";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue (res, 0, 0));
            int country_id = atoi(PQgetvalue (res, 0, 1));
            int sponsor_id = atoi(PQgetvalue (res, 0, 2));
            int captain_id = atoi(PQgetvalue (res, 0, 3));
            string name = PQgetvalue (res, 0, 4);

            return make_shared<TeamBL>(ID, country_id, sponsor_id, captain_id, name);
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
        throw GetTeamError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else
        throw GetTeamError("Unexpected getTeam error", __FILE__, __LINE__, ctime(&t_time));
}

shared_ptr<vector<TeamDTO> > TeamsRepository::getTeamsByCaptainId(int captain_id)
{
    connect();
    string query = "select * FROM teams_view where captain_id =" + to_string(captain_id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<TeamDTO>> vec = make_shared<vector<TeamDTO>>();
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
                string sponsor = PQgetvalue (res, i, 2);
                string captain = PQgetvalue (res, i, 3);
                string name = PQgetvalue (res, i, 4);
                int avg_rating = atoi(PQgetvalue (res, i, 5));

                vec->push_back(TeamDTO(ID, country, sponsor, captain, name, avg_rating));
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
        throw GetTeamError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

shared_ptr<vector<TeamDTO> > TeamsRepository::getTeamsByTournament(int tournament_id)
{
    connect();
    string query = "select * FROM tournament_teams_view where tournament_id =" + to_string(tournament_id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<TeamDTO>> vec = make_shared<vector<TeamDTO>>();
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
                string sponsor = PQgetvalue (res, i, 2);
                string captain = PQgetvalue (res, i, 3);
                string name = PQgetvalue (res, i, 4);
                int avg_rating = atoi(PQgetvalue (res, i, 5));

                vec->push_back(TeamDTO(ID, country, sponsor, captain, name, avg_rating));
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
        throw GetTeamError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

shared_ptr<vector<TeamDTO> > TeamsRepository::getAllTeams()
{
    connect();
    string query = "select * FROM teams_view;";
    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<TeamDTO>> vec = make_shared<vector<TeamDTO>>();
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
                string sponsor = PQgetvalue (res, i, 2);
                string captain = PQgetvalue (res, i, 3);
                string name = PQgetvalue (res, i, 4);
                int avg_rating = atoi(PQgetvalue (res, i, 5));

                vec->push_back(TeamDTO(ID, country, sponsor, captain, name, avg_rating));
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
        throw GetTeamError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

void TeamsRepository::addTeam(TeamBL &team_bl)
{
    //no need
}

void TeamsRepository::deleteTeam(int id)
{
    //no need
}

void TeamsRepository::updateTeam(TeamBL &team_bl, int id)
{
    //no need
}

void TeamsRepository::connect()
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
