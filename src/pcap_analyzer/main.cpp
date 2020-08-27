#include <iostream>

#include "pcap.h"
#include "pcap_structuers.h"
#include "utils.h"


int main()
{
    Pcap p{"../dump_2020-08-27_23-16-00.pcap"};
    std::cout << p.getFrames().size() << std::endl;

    return 0;
}