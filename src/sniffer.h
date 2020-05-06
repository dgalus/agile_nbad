#ifndef SNIFFER_H_
#define SNIFFER_H_

#include <string>

class Sniffer {
    public:
        Sniffer(const std::string interface);
        void sniff();

    private:
        std::string interface;
};

#endif