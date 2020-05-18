#ifndef SQLITE_DB_H_
#define SQLITE_DB_H_

#include <string>

#include <stdlib.h>
#include <sqlite3.h>

#include "idatabase.h"

class SqliteDb : public IDatabase
{
public:
    SqliteDb(std::string path);
    ~SqliteDb();
    virtual void createDbSchemaIfNotExists() override;

private:
    inline void createCountersTable();
    inline void createSuspectedIpAddressesTable();
    inline void createSuspectedDomainsTable();
    inline void createSuspectedUrlsTable();

    char *zErrMsg = 0;
    int rc;
    sqlite3* db;
};

#endif
