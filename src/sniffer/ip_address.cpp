#include "ip_address.h"

IpAddress::IpAddress()
{
    this->octets[0] = 0;
    this->octets[1] = 0;
    this->octets[2] = 0;
    this->octets[3] = 0;
}

IpAddress::IpAddress(uint8_t oct1, uint8_t oct2, uint8_t oct3, uint8_t oct4)
{
    this->octets[0] = oct1;
    this->octets[1] = oct2;
    this->octets[2] = oct3;
    this->octets[3] = oct4;
}

IpAddress::IpAddress(uint32_t ipAddress)
{
    this->octets[0] = ipAddress >> 24;
    this->octets[1] = (ipAddress >> 16) & 0xFF;
    this->octets[2] = (ipAddress >> 8) & 0xFF;
    this->octets[2] = ipAddress & 0xFF;
}

IpAddress::IpAddress(const IpAddress& ipAddress)
{
    uint32_t ip = ipAddress.toBytesBe();
    this->octets[0] = ip >> 24;
    this->octets[1] = (ip >> 16) & 0xFF;
    this->octets[2] = (ip >> 8) & 0xFF;
    this->octets[2] = ip & 0xFF;
}

std::string IpAddress::toString() const
{
    return std::to_string(this->octets[0]) + "." + std::to_string(this->octets[1]) + "." + std::to_string(this->octets[2]) + "." + std::to_string(this->octets[3]);
}

std::string IpAddress::toHexStringBe() const
{
    std::stringstream ss;
    ss << std::hex << this->octets[0] << std::hex << this->octets[1] << std::hex << this->octets[2] << std::hex << this->octets[3];
    return ss.str();
}

std::string IpAddress::toHexStringLe() const
{
    std::stringstream ss;
    ss << std::hex << this->octets[3] << std::hex << this->octets[2] << std::hex << this->octets[1] << std::hex << this->octets[0];
    return ss.str();
}

uint32_t IpAddress::toBytesBe() const
{
    uint32_t ret = this->octets[0];
    ret <<= 8;
    ret += this->octets[1];
    ret <<= 8;
    ret += this->octets[2];
    ret <<= 8;
    ret += this->octets[3];
    return ret;
}

uint32_t IpAddress::toBytesLe() const
{
    uint32_t ret = this->octets[3];
    ret <<= 8;
    ret += this->octets[2];
    ret <<= 8;
    ret += this->octets[1];
    ret <<= 8;
    ret += this->octets[0];
    return ret;
}
