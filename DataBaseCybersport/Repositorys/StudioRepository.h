#ifndef STUDIOREPOSITORY_H
#define STUDIOREPOSITORY_H

#include <libpq-fe.h>
#include <memory>
#include <vector>

using namespace std;

#include "EssensitiesDTO/StudioDTO.h"
#include "EssensitiesBL/StudioBL.h"

class StudioRepository
{
public:
    StudioRepository();
    ~StudioRepository() = default;

    shared_ptr<vector<StudioDTO>> getStudiosDTOByOwnerId(int owner_id);
    shared_ptr<vector<StudioDTO>> getAllStudios();
    void addStudio(StudioBL& studio_bl);

protected:
    void connect();

   shared_ptr<PGconn> m_connection;
};

#endif // STUDIOREPOSITORY_H
