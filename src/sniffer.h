#ifndef SNIFFER_H_
#define SNIFFER_H_

#include <functional>
#include <string>

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <linux/icmp.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define BUFSIZE 65536

class Sniffer {
    public:
        Sniffer(const std::string interface);
        void setEthernetCallback(std::function<void()> func);
        void setArpCallback(std::function<void()> func);
        void setTcpCallback(std::function<void()> func);
        void setUdpCallback(std::function<void()> func);
        void setIcmpCallback(std::function<void()> func);
        void sniff();

    private:
        void m_processFrame(char* buffer, int buflen);

        std::string interface;

        std::function<void()> ethCallback;
        std::function<void()> arpCallback;
        std::function<void()> tcpCallback;
        std::function<void()> udpCallback;
        std::function<void()> icmpCallback;
};

#endif