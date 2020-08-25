#ifndef SNIFFER_H_
#define SNIFFER_H_

#include <functional>
#include <memory>
#include <string>

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
#include <time.h>
#include <unistd.h>

#include "counters.h"
#include "pcap_writer.h"
#include "utils.h"

#define BUFSIZE 65536


class Sniffer {
public:
    Sniffer(const std::string interface, std::shared_ptr<Counters> counters, std::string filenameTemplate);
    virtual ~Sniffer();
    void sniff();

private:
    void m_processFrame(char* buffer, int buflen);
    uint8_t* blank;

    std::string filenameTemplate;
    std::string interface;
    std::shared_ptr<Counters> counters;
    PcapWriter *pw;
    uint8_t currentMinute;
};

#endif