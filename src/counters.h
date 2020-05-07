#ifndef COUNTERS_H_
#define COUNTERS_H_

class Counters
{
public:
    Counters();
    void zeroize();

    unsigned int tcp_syn;
    unsigned int tcp_ack;
    unsigned int tcp_synack;
    unsigned int tcp_psh;
    unsigned int tcp_rst;
    unsigned int tcp_fin;

    unsigned int tcp;
    unsigned int ip;
    unsigned int arp;
    unsigned int udp;
    unsigned int icmp;

    unsigned int l2_traffic;
    unsigned int l3_traffic;
    unsigned int l4_traffic;
    unsigned int l2_frames;
    unsigned int l3_frames;
    unsigned int l4_frames;
};

#endif