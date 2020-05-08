#ifndef COUNTERS_H_
#define COUNTERS_H_

#include <cstdint>
#include <mutex>

class Counters
{
public:
    Counters();
    void zeroize();

    uint64_t tcp_syn;
    uint64_t tcp_ack;
    uint64_t tcp_synack;
    uint64_t tcp_psh;
    uint64_t tcp_rst;
    uint64_t tcp_fin;

    uint64_t tcp;
    uint64_t ip;
    uint64_t arp;
    uint64_t udp;
    uint64_t icmp;

    uint64_t l2_traffic;
    uint64_t l3_traffic;
    uint64_t l4_traffic;
    uint64_t l2_frames;
    uint64_t l3_frames;
    uint64_t l4_frames;

    std::mutex counterMutex;
};

#endif