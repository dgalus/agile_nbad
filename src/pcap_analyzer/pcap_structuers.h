#ifndef PCAP_STRUCTURES_H_
#define PCAP_STRUCTURES_H_

#include <stdint.h>


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

#endif