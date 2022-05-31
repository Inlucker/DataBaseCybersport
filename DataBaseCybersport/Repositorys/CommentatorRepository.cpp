#include "CommentatorRepository.h"
#include "Errors/RepositoryErrors.h"
#include "Settings.h"

CommentatorRepository::CommentatorRepository()
{

}

shared_ptr<CommentatorBL> CommentatorRepository::getCommentator(int id)
{

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
