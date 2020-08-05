#ifndef PCAP_H_
#define PCAP_H_

#include <string>
#include <vector>

#include "pcap_structuers.h"


class Pcap
{
public:
    std::string filename;
    pcap_hdr_t header;
    std::vector<pcap_frame_s> frames;
};

#endif