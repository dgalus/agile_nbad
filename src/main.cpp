#include <fstream>
#include <iostream>
#include <sstream>

#include "../libs/rapidjson/rapidjson.h"
#include "../libs/rapidjson/document.h"

#include <chrono>
#include <iomanip>
#include <ctime>


int main(int argc, char* argv[])
{
    std::ifstream c(argv[1]);
    std::stringstream buffer;
    buffer << c.rdbuf();
    std::string _c = buffer.str();

    rapidjson::Document config;
    config.Parse(_c.c_str());

    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    std::time_t in_time_t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    std::cout << ss.str() << std::endl;
    
    std::cout << config["interface"].GetString() << std::endl;

    return 0;
}