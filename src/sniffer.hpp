#ifndef SNIFFER_HPP_
#define SNIFFER_HPP_

#include <string>

class Sniffer {
    public:
        Sniffer(const std::string interface);

    private:
        std::string interface;
};

#endif