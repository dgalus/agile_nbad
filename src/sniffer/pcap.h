#ifndef PCAP_H_
#define PCAP_H_

#include <string>
#include <vector>

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "pcap_structuers.h"


class Pcap
{
public:
    Pcap();
    Pcap(std::string filename);
    Pcap(std::string filename, std::vector<pcap_frame_t> frames, pcap_hdr_t header);
    std::string getFilename();
    void setFilename(std::string filename);
    std::vector<pcap_frame_t> getFrames();
    void setFrames(std::vector<pcap_frame_t> frames);
    pcap_hdr_t getPcapHeader();
    void setPcapHeader(pcap_hdr_t header);
    void readPcapFile(std::string filename);

private:
    std::string filename;
    std::vector<pcap_frame_t> frames;
    pcap_hdr_t header;
};

#endif