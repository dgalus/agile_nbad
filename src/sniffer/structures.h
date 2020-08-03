#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <string>
#include <vector>
#include <cstdint>

#include "ip_address.h"

#define UNKNOWN 0
#define FROM_SRC_TO_DST 1
#define FROM_DST_TO_SRC 2


struct TcpSession {
    IpAddress ip_src;
    IpAddress ip_dst;
    uint16_t src_port;
    uint16_t dst_port;
    bool is_active;
    std::string first_segm_tstmp;
    std::string last_segm_tstmp;
    std::string remote_geolocation;
};


struct TcpSessionMin {
    IpAddress ip_src;
    IpAddress ip_dst;
    uint16_t src_port;
    uint16_t dst_port;
};


struct TcpSegment {
    std::vector<std::string> flags;
    int size;
    std::string timestamp;
    int direction;
};


struct IcmpSegment {
    IpAddress ip_src;
    IpAddress ip_dst;
    uint8_t type;
    std::string timestamp;
};


struct UdpSegment {
    IpAddress ip_src;
    IpAddress ip_dst;
    uint16_t src_port;
    uint16_t dst_port;
    int size;
    std::string timestamp;
};

struct ArpPacket {
    uint16_t htype;
    uint16_t ptype;
    u_char hlen;
    u_char plen;
    uint16_t oper;
    u_char sha[6];
    u_char spa[4];
    u_char tha[6];
    u_char tpa[4];
};

struct HttpSite {
    IpAddress ip;
    std::string domain;
    std::string url;
    bool update = false;
};

#endif