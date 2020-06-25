#ifndef COUNTERS_H_
#define COUNTERS_H_

#include <cstdint>
#include <mutex>

class Counters
{
public:
    Counters();
    void zeroize();
    std::string stringifyForDb();

    uint64_t tcp_syn;
    uint64_t tcp_ack;
    uint64_t tcp_synack;
    uint64_t tcp_psh;
    uint64_t tcp_rst;
    uint64_t tcp_fin;

    uint64_t tcp_frames;
    uint64_t ip_frames;
    uint64_t arp_frames;
    uint64_t udp_frames;
    uint64_t icmp_frames;

    uint64_t l2_traffic;
    uint64_t l3_traffic;
    uint64_t l4_traffic;
    uint64_t l2_frames;
    uint64_t l3_frames;
    uint64_t l4_frames;

    std::mutex countersMutex;
};

#endif