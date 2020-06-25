#include "pcap.h"

Pcap::Pcap(std::string filename)
{
    this->filename = filename;
    pcap_hdr_t hdr;
    hdr.magic_number = 0xA1B2C3D4;
    hdr.version_major = 0x0002;
    hdr.version_minor = 0x0004;
    hdr.thiszone = 0x00000000;
    hdr.sigfigs = 0x00000000;
    hdr.snaplen = 0x00040000;
    hdr.network = 0x00000001;

    FILE *f = fopen(filename.c_str(), "wb");
    fwrite(&hdr, sizeof(hdr), 1, f);
    fclose(f);
}

void Pcap::insertFrame(void* buffer, int buflen)
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

    FILE *f = fopen(filename.c_str(), "ab+");
    fseek(f, 0, SEEK_END);
    fwrite(&ph, sizeof(pcaprec_hdr_t), 1, f);
    fwrite(buffer, buflen, 1, f);
    fclose(f);
}