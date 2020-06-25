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
    tcp_frames = 0;
    ip_frames = 0;
    arp_frames = 0;
    udp_frames = 0;
    icmp_frames = 0;
    l2_traffic = 0;
    l3_traffic = 0;
    l4_traffic = 0;
    l2_frames = 0;
    l3_frames = 0;
    l4_frames = 0;
}

std::string Counters::stringifyForDb()
{
    return "" + std::to_string(l2_traffic) + ", "
    "" + std::to_string(l2_frames) + ", "
    "" + std::to_string(l3_traffic) + ", "
    "" + std::to_string(l3_frames) + ", "
    "" + std::to_string(l4_traffic) + ", "
    "" + std::to_string(l4_frames) + ", "
    "" + std::to_string(ip_frames) + ", "
    "" + std::to_string(arp_frames) + ", "
    "" + std::to_string(icmp_frames) + ", "
    "" + std::to_string(udp_frames) + ", "
    "" + std::to_string(tcp_frames) + ", "
    "" + std::to_string(tcp_syn) + ", "
    "" + std::to_string(tcp_ack) + ", "
    "" + std::to_string(tcp_synack) + ", "
    "" + std::to_string(tcp_psh) + ", "
    "" + std::to_string(tcp_rst) + ", "
    "" + std::to_string(tcp_fin);
}
