#pragma once

#include "InstanceHost.h"

#include <boost/beast.hpp>

#include <memory>
#include <string>

namespace Spielbrett {

class WebsocketServer final : public std::enable_shared_from_this<WebsocketServer>
{
public:
    explicit WebsocketServer(std::shared_ptr<InstanceHost> instanceHost);

    void run(const std::string &listenAddr);
    void join();
    void stop();

private:
    class Session : public std::enable_shared_from_this<Session>
    {
    public:
        explicit Session(boost::asio::ip::tcp::socket&& socket, std::shared_ptr<InstanceHost> instanceHost);

        void run();
    
    private:
        void onRun();
        void onAccept(boost::beast::error_code errorCode);
        void doRead();
        void onRead(boost::beast::error_code errorCode, std::size_t bytesTransferred);
        void onWrite(boost::beast::error_code ec, std::size_t bytesTransferred);

        void handleMessage(const std::string &message);
        void sendMessage(const std::string &message);

        boost::beast::websocket::stream<boost::beast::tcp_stream> ws;
        boost::beast::flat_buffer buffer;

        std::shared_ptr<InstanceHost> instanceHost;
    };

    void doAccept();
    void onAccept(boost::beast::error_code errorCode, boost::asio::ip::tcp::socket socket);

    std::shared_ptr<InstanceHost> instanceHost;

    boost::asio::io_context ioContext;
    boost::asio::ip::tcp::acceptor acceptor;
    std::optional<std::thread> thread;
};

}
