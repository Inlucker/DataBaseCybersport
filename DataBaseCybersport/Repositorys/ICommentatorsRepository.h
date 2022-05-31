#ifndef ICOMMENTATORSREPOSITORY_H
#define ICOMMENTATORSREPOSITORY_H

#include <memory>

using namespace std;

#include "EssensitiesBL/CommentatorBL.h"

class ICommentatorsRepository
{
public:
    ICommentatorsRepository();
    virtual ~ICommentatorsRepository() = 0;

    virtual shared_ptr<CommentatorBL> getCommentator(int id) = 0;
    virtual void addCommentator(CommentatorBL& com_bl) = 0;
    virtual void deleteCommentator(int id) = 0;
    virtual void updateCommentator(CommentatorBL& com_bl, int id) = 0;
};

#endif // ICOMMENTATORSREPOSITORY_H
