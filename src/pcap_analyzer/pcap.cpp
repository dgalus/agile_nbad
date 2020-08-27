#include "pcap.h"

Pcap::Pcap()
{ }

Pcap::~Pcap()
{
    for(auto it = this->frames.begin(); it != this->frames.end(); it++)
    {
        free(it->data);
    }
}

Pcap::Pcap(std::string filename)
{
    this->readPcapFile(filename);
}

Pcap::Pcap(std::string filename, std::vector<pcap_frame_t> frames, pcap_hdr_t header)
{
    this->filename = formatStringWithDatetime(filename);
    this->frames = frames;
    this->header = header;
}

std::string Pcap::getFilename()
{
    return this->filename;
}

void Pcap::setFilename(std::string filename)
{
    this->filename = formatStringWithDatetime(filename);
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
    this->filename = formatStringWithDatetime(filename);
    uint64_t size;
    uint8_t *buffer;

    FILE *f = fopen(this->filename.c_str(), "rb");
    if(f != NULL)
    {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        rewind(f);
        buffer = (uint8_t *) malloc(size + 1);
        memset(buffer, 0, size);
        if(fread(buffer, sizeof(uint8_t), size, f) != size)
        {
            fprintf(stderr, "Unable to read whole file: %s.\n", this->filename.c_str());
        }
        memcpy(&this->header, buffer, sizeof(pcap_hdr_t));

        uint8_t *pos = buffer + sizeof(pcap_hdr_t);
        while(pos < (buffer + size))
        {
            pcap_frame_s frame;
            memcpy(&frame.header, pos, sizeof(pcaprec_hdr_s));

            frame.len = frame.header.orig_len;

            void *data = malloc(frame.len);
            memcpy(data, pos + sizeof(pcaprec_hdr_t), frame.len);
            frame.data = data;

            this->frames.push_back(frame);

            pos += frame.len + sizeof(pcaprec_hdr_t);
        }

        free(buffer);
    }
    else
    {
        fprintf(stderr, "Unable to open file: %s\n.", this->filename.c_str());
    }

    fclose(f);
}