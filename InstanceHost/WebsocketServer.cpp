#include "WebsocketServer.h"

#include <iostream>

WebsocketServer::WebsocketServer(std::shared_ptr<InstanceHost> instanceHost) :
    instanceHost(instanceHost)
{
}

void WebsocketServer::run(const std::string &listenAddr)
{
    std::cout << "WebSocket server listening on " << listenAddr << std::endl;
}

void WebsocketServer::join()
{
}

void WebsocketServer::stop()
{
    std::cout << "Shutting down the WebSocket server..." << std::endl;
}
