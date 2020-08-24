#include "pcap.h"

Pcap::Pcap()
{ }

Pcap::Pcap(std::string filename)
{
    this->readPcapFile(filename);
}

Pcap::Pcap(std::string filename, std::vector<pcap_frame_t> frames, pcap_hdr_t header)
{
    this->filename = filename;
    this->frames = frames;
    this->header = header;
}

std::string Pcap::getFilename()
{
    return this->filename;
}

void Pcap::setFilename(std::string filename)
{
    this->filename = filename;
}

std::vector<pcap_frame_t> Pcap::getFrames()
{
    return this->frames;
}

void Pcap::setFrames(std::vector<pcap_frame_t> frames)
{
    this->frames = frames;
}

pcap_hdr_t Pcap::getPcapHeader()
{
    return this->header;
}

void Pcap::setPcapHeader(pcap_hdr_t header)
{
    this->header = header;
}

void Pcap::readPcapFile(std::string filename)
{
    this->filename = filename;
    // TODO
}