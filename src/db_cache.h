#ifndef DB_CACHE_H_
#define DB_CACHE_H_

#include "idatabase.h"

class DbCache
{
public:
    DbCache(IDatabase db);

private:
    IDatabase db;
};

#endif
