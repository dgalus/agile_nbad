#ifndef IDATABASE_H_
#define IDATABASE_H_

#include <memory>
#include <string>
#include <vector>
#include "counters.h"

class IDatabase
{
public:
    virtual void createDbSchemaIfNotExists() = 0;
    virtual std::vector<std::string> getSuspectedDomains() = 0;
    virtual std::vector<std::string> getSuspectedIpAddresses() = 0;
    virtual std::vector<std::string> getSuspectedUrls() = 0;
    virtual void insertCounters(std::shared_ptr<Counters> counters) = 0;
};

#endif