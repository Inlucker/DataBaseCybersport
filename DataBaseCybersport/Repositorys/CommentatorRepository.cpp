#include "CommentatorRepository.h"
#include "Errors/RepositoryErrors.h"
#include "Settings.h"

CommentatorRepository::CommentatorRepository()
{

}

shared_ptr<CommentatorBL> CommentatorRepository::getCommentator(int id)
{

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

void CommentatorRepository::addCommentator(CommentatorBL &com_bl)
{

}

void CommentatorRepository::deleteCommentator(int id)
{

}

void CommentatorRepository::updateCommentator(CommentatorBL &com_bl, int id)
{

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
