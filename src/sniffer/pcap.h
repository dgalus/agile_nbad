#ifndef PCAP_H_
#define PCAP_H_

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <linux/icmp.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <string>

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

class Pcap
{
public:
    Pcap(std::string filename);
    void insertFrame(void* buffer, int buflen);
    void saveFileLoop();

private:
    std::string filename;
};

#endif
