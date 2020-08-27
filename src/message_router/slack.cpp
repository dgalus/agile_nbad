#include "slack.h"

Slack::Slack(std::string _api_token)
    : api_token(_api_token)
{ }

void Slack::post_message(const std::string& channel, const std::string& message)
{
    slack::_detail::Slacking& sl = slack::create(this->api_token);
    sl.chat.channel = channel;
    sl.chat.postMessage(message);
}

void Slack::post_message(const std::string& channel,
                        const std::string& message,
                        const std::string& username,
                        const std::string& emoji)
{
    slack::_detail::Slacking& sl = slack::create(this->api_token);
    slack::post(
        "chat.postMessage",
        {
            { "text", message },
            { "channel", channel },
            { "username", username },
            { "icon emoji", emoji }
        }
    );
}

void Slack::post_message(const nlohmann::json& json)
{
    slack::_detail::Slacking& sl = slack::create(this->api_token);
    slack::post("chat.postMessage", json);
}