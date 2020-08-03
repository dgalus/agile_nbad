#ifndef UTILS_H_
#define UTILS_H_

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>


static std::string getCurrentDatetime(std::string format)
{
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    std::time_t in_time_t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), format.c_str());
    return ss.str();
}

#endif