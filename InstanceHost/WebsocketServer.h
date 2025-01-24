#pragma once

#include "InstanceHost.h"

#include <string>

class WebsocketServer
{
public:
    WebsocketServer(std::shared_ptr<InstanceHost> instanceHost);

    void run(const std::string &listenAddr);
    void join();
    void stop();

private:
    std::shared_ptr<InstanceHost> instanceHost;
};
