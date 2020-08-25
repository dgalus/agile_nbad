#ifndef PCAP_WRITER_H_
#define PCAP_WRITER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include <algorithm>
#include <mutex>
#include <string>
#include <vector>

#include "utils.h"
#include "pcap_structuers.h"


class PcapWriter
{
public:
    PcapWriter(std::string filename);
    void insertFrame(void* buffer, uint16_t buflen);
    void loop();

private:
    void m_clearFrames();
    pcaprec_hdr_t m_getPcapRecHdr(uint16_t buflen);

    std::mutex frames_mutex;
    std::vector<pcap_frame_t> frames;
    std::string filename;
};

#endif
