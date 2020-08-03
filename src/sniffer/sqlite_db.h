#ifndef SQLITE_DB_H_
#define SQLITE_DB_H_

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <unistd.h>

#include "counters.h"
#include "idatabase.h"
#include "utils.h"


class SqliteDb : public IDatabase
{
public:
    SqliteDb(std::string path);
    ~SqliteDb();
    void createDbSchemaIfNotExists() override;
    void insertCounters(std::shared_ptr<Counters> counters) override;
    void insertSuspectedDomains(std::vector<std::string> suspectedDomains) override;
    void insertSuspectedIpAddresses(std::vector<std::string> suspectedIpAddresses) override;
    void insertSuspectedUrls(std::vector<std::string> suspectedUrls) override;
    std::vector<std::string> getSuspectedDomains() override;
    std::vector<std::string> getSuspectedIpAddresses() override;
    std::vector<std::string> getSuspectedUrls() override;

private:
    inline void m_createCountersTable();
    inline void m_createSuspectedIpAddressesTable();
    inline void m_createSuspectedDomainsTable();
    inline void m_createSuspectedUrlsTable();

    char *zErrMsg = 0;
    int rc;
    sqlite3* db;
};

#endif
