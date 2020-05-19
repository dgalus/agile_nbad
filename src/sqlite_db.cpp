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

void SqliteDb::insertSuspectedDomains(std::vector<std::string> suspectedDomains)
{
    sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
    std::for_each(suspectedDomains.begin(), suspectedDomains.end(), [&](const std::string& domain){
        std::string query = "INSERT INTO suspected_domain (domain) VALUES (" + domain + ");";
        sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    });
    sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, NULL);
}

void SqliteDb::insertSuspectedIpAddresses(std::vector<std::string> suspectedIpAddresses)
{
    sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
    std::for_each(suspectedIpAddresses.begin(), suspectedIpAddresses.end(), [&](const std::string& ip){
        std::string query = "INSERT INTO suspected_ip_address (domain) VALUES (" + ip + ");";
        sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    });
    sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, NULL);
}

void SqliteDb::insertSuspectedUrls(std::vector<std::string> suspectedUrls)
{
    sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
    std::for_each(suspectedUrls.begin(), suspectedUrls.end(), [&](const std::string& url){
        std::string query = "INSERT INTO suspected_url (domain) VALUES (" + url + ");";
        sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    });
    sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, NULL);
}

void SqliteDb::createCountersTable()
{
    std::string query = "CREATE TABLE counters ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
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
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "ip VARCHAR(15) NOT NULL UNIQUE);";
    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}

void SqliteDb::createSuspectedDomainsTable()
{
    std::string query = "CREATE TABLE suspected_domain ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "domain VARCHAR(250) NOT NULL UNIQUE);";
    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}

void SqliteDb::createSuspectedUrlsTable()
{
    std::string query = "CREATE TABLE suspected_url ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "url VARCHAR(1000) NOT NULL UNIQUE);";
    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}
