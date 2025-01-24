#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

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

#endif // WEBSOCKET_SERVER_H
