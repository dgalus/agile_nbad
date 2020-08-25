#include "pcap_writer.h"

PcapWriter::PcapWriter(std::string filename)
{
    pcap_hdr_t hdr;

    hdr.magic_number = 0xA1B2C3D4;
    hdr.version_major = 0x0002;
    hdr.version_minor = 0x0004;
    hdr.thiszone = 0x00000000;
    hdr.sigfigs = 0x00000000;
    hdr.snaplen = 0x00040000;
    hdr.network = 0x00000001;

    this->filename = formatStringWithDatetime(filename);

    FILE *f = fopen(this->filename.c_str(), "wb");
    fwrite(&hdr, sizeof(hdr), 1, f);
    fclose(f);
}

PcapWriter::~PcapWriter()
{
    m_loop();
    m_clearFrames();
}

void PcapWriter::insertFrame(void* buffer, uint16_t buflen)
{
    pcap_frame_s f;

    f.data = buffer;
    f.len = buflen;
    f.header = this->m_getPcapRecHdr(buflen);

    frames_mutex.lock();
    this->frames.push_back(f);
    frames_mutex.unlock();
}

void PcapWriter::m_loop()
{
    frames_mutex.lock();
    if(this->frames.size() > 300)
    {
        FILE *f = fopen(this->filename.c_str(), "ab+");
        fseek(f, 0, SEEK_END);
        for(
            std::vector<pcap_frame_t>::iterator it = this->frames.begin();
            it != this->frames.end();
            it++
            )
        {
            fwrite(&(it->header), sizeof(pcaprec_hdr_t), 1, f);
            fwrite(it->data, it->len, 1, f);
        }
        fclose(f);
        this->m_clearFrames();
    }
    frames_mutex.unlock();
}

void PcapWriter::m_clearFrames()
{
    for(
        std::vector<pcap_frame_t>::iterator it = this->frames.begin();
        it != this->frames.end();
        it++
        )
    {
        free(it->data);
    }
    this->frames.clear();
}

pcaprec_hdr_t PcapWriter::m_getPcapRecHdr(uint16_t buflen)
{
    time_t now;
    pcaprec_hdr_t ph;
    time(&now);
    ph.ts_sec = now;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    ph.ts_usec = tv.tv_usec;
    ph.incl_len = buflen;
    ph.orig_len = buflen;
    return ph;
}
