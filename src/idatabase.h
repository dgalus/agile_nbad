#ifndef IDATABASE_H_
#define IDATABASE_H_

class IDatabase
{
public:
    virtual void createDbSchemaIfNotExists() = 0;
};

#endif