#include "PlayersRepository.h"
#include "Errors/RepositoryErrors.h"
#include "Settings.h"

PlayersRepository::PlayersRepository()
{

}

shared_ptr<PlayerBL> PlayersRepository::getPlayer(int id)
{
    connect();
    string query = "select * from Players where id='" + to_string(id) + "';";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue (res, 0, 0));
            int team_id = atoi(PQgetvalue (res, 0, 1));
            int country_id = atoi(PQgetvalue (res, 0, 2));
            string nickname = PQgetvalue (res, 0, 3);
            string first_name = PQgetvalue (res, 0, 4);
            string second_name = PQgetvalue (res, 0, 5);
            int birth_year = atoi(PQgetvalue (res, 0, 6));
            string main_role = PQgetvalue (res, 0, 7);
            int rating = atoi(PQgetvalue (res, 0, 8));

            return make_shared<PlayerBL>(ID, team_id, country_id, nickname, first_name, second_name, birth_year, main_role, rating);
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
        throw GetPlayerError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else
        throw GetPlayerError("Unexpected getPlayer error", __FILE__, __LINE__, ctime(&t_time));
}

shared_ptr<vector<PlayerBL>> PlayersRepository::getFreePlayers()
{
    connect();
    string query = "select * FROM Players where team_id is null;";
    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<PlayerBL>> vec = make_shared<vector<PlayerBL>>();
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
                int team_id = atoi(PQgetvalue (res, i, 1));
                int country_id = atoi(PQgetvalue (res, i, 2));
                string nickname = PQgetvalue (res, i, 3);
                string first_name = PQgetvalue (res, i, 4);
                string second_name = PQgetvalue (res, i, 5);
                int birth_year = atoi(PQgetvalue (res, i, 6));
                string main_role = PQgetvalue (res, i, 7);
                int rating = atoi(PQgetvalue (res, i, 8));

                vec->push_back(PlayerBL(ID, team_id, country_id, nickname, first_name, second_name, birth_year, main_role, rating));
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
        throw GetPlayerError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

shared_ptr<vector<PlayerDTO> > PlayersRepository::getFreePlayersDTO()
{
    connect();
    string query = "select * FROM players_view where team_id is null;";
    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<PlayerDTO>> vec = make_shared<vector<PlayerDTO>>();
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
                string team = "No team"; //NULL
                string country = PQgetvalue (res, i, 2);
                string nickname = PQgetvalue (res, i, 3);
                string first_name = PQgetvalue (res, i, 4);
                string second_name = PQgetvalue (res, i, 5);
                int birth_year = atoi(PQgetvalue (res, i, 6));
                string main_role = PQgetvalue (res, i, 7);
                int rating = atoi(PQgetvalue (res, i, 8));

                vec->push_back(PlayerDTO(ID, team, country, nickname, first_name, second_name, birth_year, main_role, rating));
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
        throw GetPlayerError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

shared_ptr<vector<PlayerBL> > PlayersRepository::getPlayersByTeam(int team_id)
{
    connect();
    string query = "select * FROM Players where team_id =" + to_string(team_id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<PlayerBL>> vec = make_shared<vector<PlayerBL>>();
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
                int team_id = atoi(PQgetvalue (res, i, 1));
                int country_id = atoi(PQgetvalue (res, i, 2));
                string nickname = PQgetvalue (res, i, 3);
                string first_name = PQgetvalue (res, i, 4);
                string second_name = PQgetvalue (res, i, 5);
                int birth_year = atoi(PQgetvalue (res, i, 6));
                string main_role = PQgetvalue (res, i, 7);
                int rating = atoi(PQgetvalue (res, i, 8));

                vec->push_back(PlayerBL(ID, team_id, country_id, nickname, first_name, second_name, birth_year, main_role, rating));
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
        throw GetPlayerError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

shared_ptr<vector<PlayerDTO> > PlayersRepository::getPlayersDTOByTeam(int team_id)
{
    connect();
    string query = "select * FROM players_view where team_id =" + to_string(team_id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<PlayerDTO>> vec = make_shared<vector<PlayerDTO>>();
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
                string team = PQgetvalue (res, i, 1);
                string country = PQgetvalue (res, i, 2);
                string nickname = PQgetvalue (res, i, 3);
                string first_name = PQgetvalue (res, i, 4);
                string second_name = PQgetvalue (res, i, 5);
                int birth_year = atoi(PQgetvalue (res, i, 6));
                string main_role = PQgetvalue (res, i, 7);
                int rating = atoi(PQgetvalue (res, i, 8));

                vec->push_back(PlayerDTO(ID, team, country, nickname, first_name, second_name, birth_year, main_role, rating));
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
        throw GetPlayerError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

void PlayersRepository::addPlayer(PlayerBL &player_bl)
{
    connect();
    //int ID = player_bl.getId();
    string team_id = to_string(player_bl.getTeamId());
    string country_id = to_string(player_bl.getCountryId());
    string nickname = "'" + player_bl.getNickname() + "'";
    string first_name = "'" + player_bl.getFirstName() + "'";
    string second_name = "'" + player_bl.getSecondName() + "'";
    string birth_year = to_string(player_bl.getBirthYear());
    string main_role = "'" + player_bl.getMainRole() + "'";
    string rating = to_string(player_bl.getRating());

    string query = "insert into Players(team_id, country_id, nickname, first_name, second_name, birth_year, main_role, rating) values(";
    query += team_id + ", ";
    query += country_id + ", ";
    query += nickname + ", ";
    query += first_name + ", ";
    query += second_name + ", ";
    query += birth_year + ", ";
    query += main_role + ", ";
    query += rating + ");";
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
        throw InsertPlayerError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    }
}

void PlayersRepository::deletePlayer(int id)
{
    //Не нужно
}

void PlayersRepository::updatePlayer(PlayerBL &player_bl, int id)
{
    connect();
    string team_id = "NULL";
    if (player_bl.getTeamId() != 0)
        team_id = to_string(player_bl.getTeamId());
    string country_id = to_string(player_bl.getCountryId());
    string nickname = "'" + player_bl.getNickname() + "'";
    string first_name = "'" + player_bl.getFirstName() + "'";
    string second_name = "'" + player_bl.getSecondName() + "'";
    string birth_year = to_string(player_bl.getBirthYear());
    string main_role = "'" + player_bl.getMainRole() + "'";
    string rating = to_string(player_bl.getRating());

    string query = "update Players set team_id = " + team_id;
    query += ", country_id = " + country_id;
    query += ", nickname = " + nickname;
    query += ", first_name = " + first_name;
    query += ", second_name = " + second_name;
    query += ", birth_year = " + birth_year;
    query += ", main_role = " + main_role;
    query += ", rating = " + rating;
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
        throw UpdatePlayerError("No such Player", __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 2)
        throw UpdatePlayerError(error_msg, __FILE__, __LINE__, ctime(&t_time));
}

void PlayersRepository::connect()
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
