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
    void createDbSchemaIfNotExists() override;
    void insertCounters(std::shared_ptr<Counters> counters) override;
    std::vector<std::string> getSuspectedDomains() override;
    std::vector<std::string> getSuspectedIpAddresses() override;
    std::vector<std::string> getSuspectedUrls() override;

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
