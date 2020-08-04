#ifndef PCAP_READER_H_
#define PCAP_READER_H_

#include <string>

#include "pcap_structuers.h"


class PcapReader
{
public:
    PcapReader(std::string filename);
    void read();

private:
    std::string filename;
};

#endif