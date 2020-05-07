#include "counters.h"

Counters::Counters()
{ }

void Counters::zeroize()
{
    tcp_syn = 0;
    tcp_ack = 0;
    tcp_synack = 0;
    tcp_psh = 0;
    tcp_rst = 0;
    tcp_fin = 0;
    tcp = 0;
    ip = 0;
    arp = 0;
    udp = 0;
    icmp = 0;
    l2_traffic = 0;
    l3_traffic = 0;
    l4_traffic = 0;
    l2_frames = 0;
    l3_frames = 0;
    l4_frames = 0;
}