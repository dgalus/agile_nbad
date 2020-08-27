#ifndef UTILS_H_
#define UTILS_H_

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>


static std::string formatStringWithDatetime(std::string str)
{
    std::string input = str;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), str.c_str());
    return ss.str();
}

static std::string getCurrentDatetime(std::string format)
{
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    std::time_t in_time_t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), format.c_str());
    return ss.str();
}

static uint8_t getCurrentMinute()
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    return now->tm_min;
}

#endif