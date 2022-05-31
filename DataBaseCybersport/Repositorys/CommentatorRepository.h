#ifndef COMMENTATORREPOSITORY_H
#define COMMENTATORREPOSITORY_H

#include <libpq-fe.h>

#include "ICommentatorsRepository.h"
#include "EssensitiesDTO/CommentatorDTO.h"

class CommentatorRepository : public ICommentatorsRepository
{
public:
    CommentatorRepository();
    ~CommentatorRepository() = default;

    virtual shared_ptr<CommentatorBL> getCommentator(int id) override;
    virtual void addCommentator(CommentatorBL& com_bl) override;
    virtual void deleteCommentator(int id) override;
    virtual void updateCommentator(CommentatorBL& com_bl, int id) override;

protected:
    void connect();

    shared_ptr<PGconn> m_connection;
};

#endif // COMMENTATORREPOSITORY_H
