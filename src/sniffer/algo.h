#ifndef ALGO_H_
#define ALGO_H_

#include <chrono>
#include <ctime>
#include <iomanip>
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

#endif