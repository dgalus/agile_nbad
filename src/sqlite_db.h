#ifndef SQLITE_DB_H_
#define SQLITE_DB_H_

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include <sqlite3.h>

#include "counters.h"
#include "idatabase.h"

class SqliteDb : public IDatabase
{
public:
    SqliteDb(std::string path);
    ~SqliteDb();
    virtual void createDbSchemaIfNotExists() override;
    virtual std::vector<std::string> getSuspectedDomains() override;
    virtual std::vector<std::string> getSuspectedIpAddresses() override;
    virtual std::vector<std::string> getSuspectedUrls() override;
    virtual void insertCounters(std::shared_ptr<Counters> counters) override;

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
