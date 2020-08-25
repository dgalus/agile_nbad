#include "sniffer.h"

Sniffer::Sniffer(const std::string interface, std::shared_ptr<Counters> counters, std::string filenameTemplate)
{
    this->interface = interface;
    this->counters = counters;
    this->filenameTemplate = filenameTemplate;
    this->blank = (uint8_t *) malloc(6);
    memset(blank, 0, 6);
    this->pw = new PcapWriter(filenameTemplate);
    this->currentMinute = getCurrentMinute();
}

Sniffer::~Sniffer()
{
    free(this->blank);
    delete this->pw;
}

void Sniffer::sniff()
{
    int sock_r;
    int buflen;

    sock_r = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(sock_r < 0)
    {
        perror("error in socket()\n");
        exit(2);
    }

    struct ifreq ifr;
    struct sockaddr_ll ll;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, this->interface.c_str(), sizeof(ifr.ifr_name));
    if(ioctl(sock_r, SIOCGIFINDEX, &ifr) < 0)
    {
        perror("ioctl[SIOCGIFINDEX]");
        close(sock_r);
        exit(3);
    }

    memset(&ll, 0, sizeof(ll));
    ll.sll_family = AF_PACKET;
    ll.sll_ifindex = ifr.ifr_ifindex;
    ll.sll_protocol = htons(ETH_P_ALL);
    if(bind(sock_r, (struct sockaddr *) &ll, sizeof(ll)) < 0)
    {
        perror("bind[AF_PACKET]");
        close(sock_r);
        exit(4);
    }

    struct packet_mreq mr;
    memset(&mr, 0, sizeof(mr));
    mr.mr_ifindex = ll.sll_ifindex;
    mr.mr_type = PACKET_MR_PROMISC;
    if(setsockopt(sock_r, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof(mr)) < 0)
    {
        perror("setsockopt[PACKET_MR_PROMISC]");
        close(sock_r);
        exit(5);
    }

    char *buffer = (char *) malloc(BUFSIZE);

    while(true)
    {
        memset(buffer, 0, BUFSIZE);

        buflen = recvfrom(sock_r, buffer, BUFSIZE, 0, NULL, NULL);
        if(buflen < 0)
        {
            perror("error in recvfrom()\n");
            continue;
        }
        uint8_t currMin = getCurrentMinute();
        if(currMin != this->currentMinute)
        {
            this->currentMinute = currMin;
            delete this->pw;
            this->pw = new PcapWriter(filenameTemplate);
        }
        this->pw->insertFrame(buffer, buflen);
        this->m_processFrame(buffer, buflen);
    }

    free(buffer);
}

void Sniffer::m_processFrame(char* buffer, int buflen)
{
    struct ethhdr *eth = (struct ethhdr *)(buffer);
    if((!memcmp(this->blank, eth->h_source, 6)) && (!memcmp(this->blank, eth->h_dest, 6)))
        return;
    this->counters->countersMutex.lock();
    this->counters->l2_frames++;
    this->counters->l2_traffic += buflen;
    this->counters->countersMutex.unlock();

    if(eth->h_proto == 0x0608)
    {
        this->counters->countersMutex.lock();
        this->counters->l3_frames++;
        this->counters->l3_traffic += (buflen - sizeof(struct ethhdr));
        this->counters->arp_frames++;
        this->counters->countersMutex.unlock();
        // TODO
    }
    else if(eth->h_proto == 0x0008)
    {
        this->counters->countersMutex.lock();
        this->counters->l3_frames++;
        this->counters->l3_traffic += (buflen - sizeof(struct ethhdr));
        this->counters->ip_frames++;
        this->counters->countersMutex.unlock();

        unsigned short iphdrlen;
        struct iphdr *iph = (struct iphdr*) (buffer + sizeof(struct ethhdr));
        iphdrlen = iph->ihl * 4;

        // TODO
        if(iph->protocol == 1)
        {
            this->counters->countersMutex.lock();
            this->counters->l4_frames++;
            this->counters->l4_traffic += (buflen - sizeof(struct ethhdr) - iphdrlen);
            this->counters->icmp_frames++;
            this->counters->countersMutex.unlock();

            // TODO
        }
        else if(iph->protocol == 6)
        {
            this->counters->countersMutex.lock();
            this->counters->l4_frames++;
            this->counters->l4_traffic += (buflen - sizeof(struct ethhdr) - iphdrlen);
            this->counters->tcp_frames++;
            this->counters->countersMutex.unlock();

            // TODO
        }
        else if(iph->protocol == 17)
        {
            this->counters->countersMutex.lock();
            this->counters->l4_frames++;
            this->counters->l4_traffic += (buflen - sizeof(struct ethhdr) - iphdrlen);
            this->counters->udp_frames++;
            this->counters->countersMutex.unlock();

            // TODO
        }
    }
}