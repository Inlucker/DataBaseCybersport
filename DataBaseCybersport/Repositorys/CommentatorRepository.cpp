#include "CommentatorRepository.h"
#include "Errors/RepositoryErrors.h"
#include "Settings.h"

CommentatorRepository::CommentatorRepository()
{

}

shared_ptr<CommentatorBL> CommentatorRepository::getCommentator(int id)
{
    connect();
    string query = "select * from Commentators where id='" + to_string(id) + "';";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue (res, 0, 0));
            int studio_id = atoi(PQgetvalue (res, 0, 1));
            int country_id = atoi(PQgetvalue (res, 0, 2));
            string nickname = PQgetvalue (res, 0, 3);
            string first_name = PQgetvalue (res, 0, 4);
            string second_name = PQgetvalue (res, 0, 5);
            int birth_year = atoi(PQgetvalue (res, 0, 6));
            int popularity = atoi(PQgetvalue (res, 0, 7));

            return make_shared<CommentatorBL>(ID, studio_id, country_id, nickname, first_name, second_name, birth_year, popularity);
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
        throw GetCommentatorError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else
        throw GetCommentatorError("Unexpected getCommentator error", __FILE__, __LINE__, ctime(&t_time));
}

shared_ptr<vector<CommentatorDTO> > CommentatorRepository::getCommentatorsDTOByStudioId(int studio_id)
{
    connect();
    string query = "select * FROM commentators_view where studio_id ";

    if (studio_id == 0)
        query += "is NULL;";
    else
        query += "=" + to_string(studio_id) + ";";

    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<CommentatorDTO>> vec = make_shared<vector<CommentatorDTO>>();
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
                string studio = PQgetvalue (res, i, 1);
                if (studio_id == 0)
                    studio = "No studio";
                string country = PQgetvalue (res, i, 2);
                string nickname = PQgetvalue (res, i, 3);
                string first_name = PQgetvalue (res, i, 4);
                string second_name = PQgetvalue (res, i, 5);
                int birth_year = atoi(PQgetvalue (res, i, 6));
                int rating = atoi(PQgetvalue (res, i, 7));

                vec->push_back(CommentatorDTO(ID, studio, country, nickname, first_name, second_name, birth_year, rating));
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
        throw GetCommentatorError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

shared_ptr<vector<CommentatorDTO> > CommentatorRepository::getCommentatorsDTOByOwnerId(int owner_id)
{
    connect();
    string query = "select * FROM commentators_view where owner_id ";

    if (owner_id == 0)
        query += "is NULL;";
    else
        query += "=" + to_string(owner_id) + " order by studio_id, id;";

    PQsendQuery(m_connection.get(), query.c_str());

    shared_ptr<vector<CommentatorDTO>> vec = make_shared<vector<CommentatorDTO>>();
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
                string studio = PQgetvalue (res, i, 1);
                string country = PQgetvalue (res, i, 2);
                string nickname = PQgetvalue (res, i, 3);
                string first_name = PQgetvalue (res, i, 4);
                string second_name = PQgetvalue (res, i, 5);
                int birth_year = atoi(PQgetvalue (res, i, 6));
                int rating = atoi(PQgetvalue (res, i, 7));

                vec->push_back(CommentatorDTO(ID, studio, country, nickname, first_name, second_name, birth_year, rating));
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
        throw GetCommentatorError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

void CommentatorRepository::addCommentator(CommentatorBL &com_bl)
{

}

void CommentatorRepository::deleteCommentator(int id)
{

}

void CommentatorRepository::updateCommentator(CommentatorBL &com_bl, int id)
{
    connect();
    string studio_id = "NULL";
    if (com_bl.getStudioId() != 0)
        studio_id = to_string(com_bl.getStudioId());
    string country_id = to_string(com_bl.getCountryId());
    string nickname = "'" + com_bl.getNickname() + "'";
    string first_name = "'" + com_bl.getFirstName() + "'";
    string second_name = "'" + com_bl.getSecondName() + "'";
    string birth_year = to_string(com_bl.getBirthYear());
    string popularity = to_string(com_bl.getPopularity());

    string query = "update Commentators set studio_id = " + studio_id;
    query += ", country_id = " + country_id;
    query += ", nickname = " + nickname;
    query += ", first_name = " + first_name;
    query += ", second_name = " + second_name;
    query += ", birth_year = " + birth_year;
    query += ", popularity = " + popularity;
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
        throw UpdateCommentatorError("No such Commentator", __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 2)
        throw UpdateCommentatorError(error_msg, __FILE__, __LINE__, ctime(&t_time));
}

void CommentatorRepository::connect()
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
