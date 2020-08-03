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
    m_createCountersTable();
    m_createSuspectedDomainsTable();
    m_createSuspectedIpAddressesTable();
    m_createSuspectedUrlsTable();
}

std::vector<std::string> SqliteDb::getSuspectedDomains()
{
    sqlite3_stmt *stmt;
    std::string query = "SELECT domain FROM suspected_domain;";
    rc = sqlite3_prepare(db, query.c_str(), 0, &stmt, 0);
    if(rc != SQLITE_OK) {
        return std::vector<std::string>{};
    } else {
        std::vector<std::string> ret;
        while((rc = sqlite3_step(stmt)) != SQLITE_DONE)
        {
            switch(rc)
            {
                case SQLITE_BUSY:
                    usleep(300);
                    break;
                case SQLITE_ERROR:
                    break;
                case SQLITE_ROW:
                    int n = sqlite3_column_count(stmt);
                    for(int i=0; i<n; i++)
                        ret.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))));
            }
        }
        sqlite3_finalize(stmt);
        return ret;
    }
}

std::vector<std::string> SqliteDb::getSuspectedIpAddresses()
{
    sqlite3_stmt *stmt;
    std::string query = "SELECT ip FROM suspected_ip_address;";
    rc = sqlite3_prepare(db, query.c_str(), 0, &stmt, 0);
    if(rc != SQLITE_OK) {
        return std::vector<std::string>{};
    } else {
        std::vector<std::string> ret;
        while((rc = sqlite3_step(stmt)) != SQLITE_DONE)
        {
            switch(rc)
            {
                case SQLITE_BUSY:
                    usleep(300);
                    break;
                case SQLITE_ERROR:
                    break;
                case SQLITE_ROW:
                    int n = sqlite3_column_count(stmt);
                    for(int i=0; i<n; i++)
                        ret.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))));
            }
        }
        sqlite3_finalize(stmt);
        return ret;
    }
}

std::vector<std::string> SqliteDb::getSuspectedUrls()
{
    sqlite3_stmt *stmt;
    std::string query = "SELECT url FROM suspected_url;";
    rc = sqlite3_prepare(db, query.c_str(), 0, &stmt, 0);
    if(rc != SQLITE_OK) {
        return std::vector<std::string>{};
    } else {
        std::vector<std::string> ret;
        while((rc = sqlite3_step(stmt)) != SQLITE_DONE)
        {
            switch(rc)
            {
                case SQLITE_BUSY:
                    usleep(300);
                    break;
                case SQLITE_ERROR:
                    break;
                case SQLITE_ROW:
                    int n = sqlite3_column_count(stmt);
                    for(int i=0; i<n; i++)
                        ret.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))));
            }
        }
        sqlite3_finalize(stmt);
        return ret;
    }
}

void SqliteDb::insertCounters(std::shared_ptr<Counters> counters)
{
    std::string timestamp = getCurrentDatetime("%Y-%m-%d %X");
    counters->countersMutex.lock();
    std::string query = "INSERT INTO counters ("
        "timestamp, l2_traffic, l2_frames, l3_traffic, l3_frames, "
        "l4_traffic, l4_frames, ip_frames, arp_frames, icmp_frames, "
        "udp_frames, tcp_frames, tcp_syn, tcp_ack, tcp_synack, tcp_psh, "
        "tcp_rst, tcp_fin) VALUES (" + timestamp + ""
        "" + counters->stringifyForDb() + ""
        ")";

    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
    counters->zeroize();
    counters->countersMutex.unlock();
}

void SqliteDb::insertSuspectedDomains(std::vector<std::string> suspectedDomains)
{
    sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
    std::for_each(suspectedDomains.begin(), suspectedDomains.end(), [&](const std::string& domain){
        std::string query = "INSERT INTO suspected_domain (domain) VALUES (" + domain + ");";
        sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    });
    sqlite3_exec(db, "COMMIT TRANSACTION", NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}

void SqliteDb::insertSuspectedIpAddresses(std::vector<std::string> suspectedIpAddresses)
{
    sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
    std::for_each(suspectedIpAddresses.begin(), suspectedIpAddresses.end(), [&](const std::string& ip){
        std::string query = "INSERT INTO suspected_ip_address (domain) VALUES (" + ip + ");";
        sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    });
    sqlite3_exec(db, "COMMIT TRANSACTION", NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}

void SqliteDb::insertSuspectedUrls(std::vector<std::string> suspectedUrls)
{
    sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
    std::for_each(suspectedUrls.begin(), suspectedUrls.end(), [&](const std::string& url){
        std::string query = "INSERT INTO suspected_url (domain) VALUES (" + url + ");";
        sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    });
    sqlite3_exec(db, "COMMIT TRANSACTION", NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}

void SqliteDb::m_createCountersTable()
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

void SqliteDb::m_createSuspectedIpAddressesTable()
{
    std::string query = "CREATE TABLE suspected_ip_address ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "ip VARCHAR(15) NOT NULL UNIQUE);";
    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}

void SqliteDb::m_createSuspectedDomainsTable()
{
    std::string query = "CREATE TABLE suspected_domain ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "domain VARCHAR(250) NOT NULL UNIQUE);";
    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}

void SqliteDb::m_createSuspectedUrlsTable()
{
    std::string query = "CREATE TABLE suspected_url ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "url VARCHAR(1000) NOT NULL UNIQUE);";
    rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }
}
