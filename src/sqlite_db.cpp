#include "sqlite_db.h"

SqliteDb::SqliteDb(std::string path)
{
    rc = sqlite3_open(path.c_str(), &db);
    if(rc) {
        fprintf(stderr, "Cannot open database %s.\n", sqlite3_errmsg(db));
    }
}

SqliteDb::~SqliteDb()
{
    sqlite3_close(db);
    free(db);
}

void SqliteDb::createDbSchemaIfNotExists()
{
    createCountersTable();
    createSuspectedDomainsTable();
    createSuspectedIpAddressesTable();
    createSuspectedUrlsTable();
}

std::vector<std::string> SqliteDb::getSuspectedDomains()
{
    std::vector<std::string> ret;
    return ret;
}

std::vector<std::string> SqliteDb::getSuspectedIpAddresses()
{
    std::vector<std::string> ret;
    return ret;
}

std::vector<std::string> SqliteDb::getSuspectedUrls()
{
    std::vector<std::string> ret;
    return ret;
}

void SqliteDb::insertCounters(std::shared_ptr<Counters> counters)
{

}

void SqliteDb::createCountersTable()
{
    std::string query = "CREATE TABLE counters ("
        "id INTEGER PRIMARY KEY, "
        "timestamp DATETIME NOT NULL UNIQUE, "
        "l2_traffic BIGINT NOT NULL, "
        "l2_frames BIGINT NOT NULL, "
        "l3_traffic BIGINT NOT NULL, "
        "l3_frames BIGINT NOT NULL, "
        "l4_traffic BIGINT NOT NULL, "
        "l4_frames BIGINT NOT NULL, "
        "ip_frames BIGINT NOT NULL, "
        "arp_frames BIGINT NOT NULL, "
        "icmp_frames BIGINT NOT NULL, "
        "udp_frames BIGINT NOT NULL, "
        "tcp_frames BIGINT NOT NULL, "
        "tcp_syn BIGINT NOT NULL, "
        "tcp_ack BIGINT NOT NULL, "
        "tcp_synack BIGINT NOT NULL, "
        "tcp_psh BIGINT NOT NULL, "
        "tcp_rst BIGINT NOT NULL, "
        "tcp_fin BIGINT NOT NULL"
        ");";
    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}

void SqliteDb::createSuspectedIpAddressesTable()
{
    std::string query = "CREATE TABLE suspected_ip_address ("
        "id INTEGER PRIMARY KEY, "
        "ip VARCHAR(15) NOT NULL UNIQUE);";
    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}

void SqliteDb::createSuspectedDomainsTable()
{
    std::string query = "CREATE TABLE suspected_domain ("
        "id INTEGER PRIMARY KEY, "
        "domain VARCHAR(250) NOT NULL UNIQUE);";
    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}

void SqliteDb::createSuspectedUrlsTable()
{
    std::string query = "CREATE TABLE suspected_url ("
        "id INTEGER PRIMARY KEY, "
        "url VARCHAR(1000) NOT NULL UNIQUE);";
    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}
