#include "TournamentsRepository.h"
#include "Errors/RepositoryErrors.h"
#include "Settings.h"

TournamentsRepository::TournamentsRepository()
{

}

shared_ptr<vector<TournamentDTO> > TournamentsRepository::getTournamentsDTOByOrgId(int org_id)
{
    connect();
    string query = "select * FROM tournaments_view where organizer_id =" + to_string(org_id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<TournamentDTO>> vec = make_shared<vector<TournamentDTO>>();
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
                string organizer = PQgetvalue (res, i, 2);
                string name = PQgetvalue (res, i, 3);
                int prize_pool = atoi(PQgetvalue (res, i, 4));

                vec->push_back(TournamentDTO(ID, country, organizer, name, prize_pool));
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
        throw GetTournamentError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

int TournamentsRepository::addTournament(TournamentBL &tournament_bl)
{
    connect();
    //int ID = player_bl.getId();
    string country_id = to_string(tournament_bl.getCountryId());
    string organizer_id = to_string(tournament_bl.getOrganizerId());
    string name = "'" + tournament_bl.getName() + "'";
    string prize_pool = to_string(tournament_bl.getPrizePool());

    string query = "insert into Tournaments(country_id, organizer_id, name, prizepool) values(";
    query += country_id + ", ";
    query += organizer_id + ", ";
    query += name + ", ";
    query += prize_pool + ") RETURNING id;";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue(res, 0, 0));
            return ID;
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
        throw InsertTournamentError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else
        throw InsertTournamentError("Unexpected addTournament error", __FILE__, __LINE__, ctime(&t_time));

}

void TournamentsRepository::addTournamentTeams(int tournament_id, shared_ptr<vector<int> > teams_id)
{
    connect();
    string query = "";
    string ID = to_string(tournament_id);
    for (auto &id : *teams_id)
    {
        query += "insert into TournamentTeams values (";
        query += ID + ", ";
        query += to_string(id) + ");\n";
    }
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
        throw InsertTournamentError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    }
}

void TournamentsRepository::connect()
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
