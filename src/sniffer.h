#ifndef SNIFFER_H_
#define SNIFFER_H_

#include <functional>
#include <string>

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
        std::string interface;
        std::function<void()> ethCallback;
        std::function<void()> arpCallback;
        std::function<void()> tcpCallback;
        std::function<void()> udpCallback;
        std::function<void()> icmpCallback;
};

#endif