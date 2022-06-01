#include "MatchesRepository.h"
#include "Errors/RepositoryErrors.h"
#include "Settings.h"

MatchesRepository::MatchesRepository()
{

}

shared_ptr<vector<MatchDTO> > MatchesRepository::getMatchesDTOByTournament(int tournament_id)
{
    connect();
    string query = "select * FROM matches_view where tournament_id =" + to_string(tournament_id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<MatchDTO>> vec = make_shared<vector<MatchDTO>>();
    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        int rows_n = PQntuples(res);
        if (PQresultStatus(res) == PGRES_TUPLES_OK && rows_n)
        {
            for (int i = 0; i < rows_n; i++)
            {
                //int ID = atoi(PQgetvalue (res, i, 0));
                string team1 = PQgetvalue (res, i, 0);
                string team2 = PQgetvalue (res, i, 1);
                string winner = PQgetvalue (res, i, 2);
                string studio = PQgetvalue (res, i, 3);
                string commentator = PQgetvalue (res, i, 4);
                string tournament = PQgetvalue (res, i, 5);
                string date = PQgetvalue (res, i, 6);

                vec->push_back(MatchDTO(team1, team2, winner, studio, commentator, tournament, date));
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
        throw GetMatchError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

void MatchesRepository::addMatch(MatchBL &match)
{
    connect();

    string team1_id = to_string(match.getTeam1Id());
    string team2_id = to_string(match.getTeam2Id());
    string winner_id = to_string(match.getWinnerId());
    string studio_id = to_string(match.getStudioId());
    string commentator_id = to_string(match.getCommentatorId());
    string tournament_id = to_string(match.getTournamentId());
    string date = "'" + match.getDate() + "'";


    string query = "insert into Matches values(";
    query += team1_id + ", ";
    query += team2_id + ", ";
    query += winner_id + ", ";
    query += studio_id + ", ";
    query += commentator_id + ", ";
    query += tournament_id + ", ";
    query += date + ");";
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
        throw InsertMatchError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    }
}

void MatchesRepository::connect()
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
