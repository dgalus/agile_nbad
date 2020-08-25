#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

#include "counters.h"
#include "sniffer.h"
#include "pcap.h"

#include "../../libs/rapidjson/rapidjson.h"
#include "../../libs/rapidjson/document.h"

void printUsage(char* app)
{
    std::cerr << "USAGE:\n\t" << app << " <CONFIG_PATH>" << std::endl;
    exit(1);
}

void getConfig(char* path, rapidjson::Document& config)
{
    std::ifstream c{path};
    std::stringstream buffer;
    buffer << c.rdbuf();
    std::string _c = buffer.str();
    config.Parse(_c.c_str());
}

int main(int argc, char* argv[])
{
    if(argc < 2)
        printUsage(argv[0]);

    rapidjson::Document config;
    getConfig(argv[1], config);

    std::shared_ptr<Counters> c = std::make_shared<Counters>();
    Sniffer s{config["interface"].GetString(), c, config["pcap_file_template"].GetString()};
    //Pcap p{config["pcap_file_template"].GetString()};

    return 0;
}