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
                int ID = atoi(PQgetvalue (res, i, 0));
                string team1 = PQgetvalue (res, i, 1);
                string team2 = PQgetvalue (res, i, 2);
                string winner = PQgetvalue (res, i, 3);
                string studio = PQgetvalue (res, i, 4);
                string commentator = PQgetvalue (res, i, 5);
                string tournament = PQgetvalue (res, i, 6);
                string date = PQgetvalue (res, i, 7);

                vec->push_back(MatchDTO(ID, team1, team2, winner, studio, commentator, tournament, date));
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

shared_ptr<MatchBL> MatchesRepository::getMatch(int match_id)
{
    connect();
    string query = "select * FROM Matches where id =" + to_string(match_id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue (res, 0, 0));
            int team1_id = atoi(PQgetvalue (res, 0, 1));
            int team2_id = atoi(PQgetvalue (res, 0, 2));
            int winner_id = atoi(PQgetvalue (res, 0, 3));
            int studio_id = atoi(PQgetvalue (res, 0, 4));
            int commentator_id = atoi(PQgetvalue (res, 0, 5));
            int tournament_id = atoi(PQgetvalue (res, 0, 6));
            string date = PQgetvalue (res, 0, 7);

            return make_shared<MatchBL>(ID, team1_id, team2_id, winner_id, studio_id, commentator_id, tournament_id, date);
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
    else
        throw GetMatchError("Unexpected getMatch error", __FILE__, __LINE__, ctime(&t_time));
}

void MatchesRepository::addMatch(MatchBL &match)
{
    connect();

    string team1_id = to_string(match.getTeam1Id());
    string team2_id = to_string(match.getTeam2Id());
    int w_id = match.getWinnerId();
    string winner_id = to_string(w_id);
    if (w_id <= 0)
        winner_id = "NULL";
    string studio_id = to_string(match.getStudioId());
    string commentator_id = to_string(match.getCommentatorId());
    string tournament_id = to_string(match.getTournamentId());
    string date = "'" + match.getDate() + "'";


    string query = "insert into Matches(team1_id, team2_id, winner_id, studio_id, commentator_id, tournament_id, date) values(";
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

void MatchesRepository::updateMatch(MatchBL &match, int match_id)
{
    connect();
    string team1_id = to_string(match.getTeam1Id());
    string team2_id = to_string(match.getTeam2Id());
    int w_id = match.getWinnerId();
    string winner_id = to_string(w_id);
    if (w_id <= 0)
        winner_id = "NULL";
    string studio_id = to_string(match.getStudioId());
    string commentator_id = to_string(match.getCommentatorId());
    string tournament_id = to_string(match.getTournamentId());
    string date = "'" + match.getDate() + "'";

    string query = "update Matches set team1_id = " + team1_id;
    query += ", team2_id = " + team2_id;
    query += ", winner_id = " + winner_id;
    query += ", studio_id = " + studio_id;
    query += ", commentator_id = " + commentator_id;
    query += ", tournament_id = " + tournament_id;
    query += ", date = " + date;
    query += " where id = " + to_string(match_id) + ";";
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
        throw UpdateMatchError("No such Match", __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 2)
        throw UpdateMatchError(error_msg, __FILE__, __LINE__, ctime(&t_time));
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
