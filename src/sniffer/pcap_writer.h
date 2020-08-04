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

#include "algo.h"


typedef struct pcap_hdr_s {
    uint32_t magic_number;
    uint16_t version_major;
    uint16_t version_minor;
    int32_t  thiszone;
    uint32_t sigfigs;
    uint32_t snaplen;
    uint32_t network;
} pcap_hdr_t;


typedef struct pcaprec_hdr_s {
    uint32_t ts_sec;
    uint32_t ts_usec;
    uint32_t incl_len;
    uint32_t orig_len;
} pcaprec_hdr_t;


typedef struct pcap_frame_s {
    pcaprec_hdr_s header;
    uint16_t len;
    void* data;
} pcap_frame_t;


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
