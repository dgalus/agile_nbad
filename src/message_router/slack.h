#ifndef SLACK_H_
#define SLACK_H_

#include <fstream>
#include <string>

#include "../../libs/slacking/json.hpp"
#include "../../libs/slacking/slacking.hpp"

class Slack
{
public:
    Slack(std::string api_token);
    void post_message(const std::string& channel, const std::string& message);
    void post_message(const std::string& channel, const std::string& message,
                    const std::string& username, const std::string& emoji);
    void post_message(const nlohmann::json& json);

private:
    std::string api_token;
};

#endif