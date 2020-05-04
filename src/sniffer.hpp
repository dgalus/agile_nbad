#ifndef SNIFFER_HPP_
#define SNIFFER_HPP_

#include <string>

class Sniffer {
    public:
        Sniffer(const std::string interface);
        void sniff();

    private:
        std::string interface;
};

#endif