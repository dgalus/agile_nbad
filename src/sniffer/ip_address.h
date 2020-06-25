#ifndef IP_ADDRESS_H_
#define IP_ADDRESS_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <sstream>

class IpAddress
{
public:
    IpAddress();
    IpAddress(uint8_t oct1, uint8_t oct2, uint8_t oct3, uint8_t oct4);
    IpAddress(uint32_t ipAddress);
    IpAddress(const IpAddress& ipAddress);
    std::string to_string() const;
    std::string to_hex_string_be() const;
    std::string to_hex_string_le() const;
    uint32_t to_bytes_be() const;
    uint32_t to_bytes_le() const;
private:
    uint8_t octets[4];
};

#endif