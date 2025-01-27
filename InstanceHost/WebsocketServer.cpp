#include "WebsocketServer.h"

#include <boost/algorithm/string.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast.hpp>

#include <iostream>
#include <memory>
#include <stdexcept>

namespace Spielbrett {

WebsocketServer::WebsocketServer(std::shared_ptr<InstanceHost> instanceHost) :
    std::enable_shared_from_this<WebsocketServer>(),
    instanceHost(instanceHost),
    ioContext(1),
    acceptor(ioContext)
{
}

void WebsocketServer::run(const std::string &listenAddr)
{
    std::vector<std::string> tokens;
    boost::split(tokens, listenAddr, boost::is_any_of(":"));
    if (tokens.size() != 2) {
        throw std::invalid_argument("invalid listenAddr format");
    }
    auto const address = boost::asio::ip::make_address(tokens[0]);
    auto const port = static_cast<unsigned short>(std::stoi(tokens[1]));
    boost::asio::ip::tcp::endpoint endpoint{address, port};

    boost::beast::error_code errorCode;

    acceptor.open(endpoint.protocol(), errorCode);
    if (errorCode) {
        std::stringstream ss;
        ss << "failed to open acceptor: error code: " << errorCode.to_string();
        throw std::runtime_error(ss.str());
    }

    acceptor.set_option(boost::asio::socket_base::reuse_address(true), errorCode);
    if (errorCode) {
        std::stringstream ss;
        ss << "failed to set_option: error code: " << errorCode.to_string();
        throw std::runtime_error(ss.str());
    }

    acceptor.bind(endpoint, errorCode);
    if (errorCode) {
        std::stringstream ss;
        ss << "failed to bind acceptor: error code: " << errorCode.to_string();
        throw std::runtime_error(ss.str());
    }

    doAccept();

    thread = std::thread([self = shared_from_this()] {
        self->ioContext.run();
    });

    std::cout << "WebSocket server listening on " << listenAddr << std::endl;
}

void WebsocketServer::join()
{
    thread->join();
}

void WebsocketServer::stop()
{
    ioContext.stop();
    std::cout << "Shutting down the WebSocket server..." << std::endl;
}

void WebsocketServer::doAccept()
{
    acceptor.async_accept(
        boost::asio::make_strand(ioContext),
        boost::beast::bind_front_handler(&WebsocketServer::onAccept, shared_from_this()));
}

void WebsocketServer::onAccept(boost::beast::error_code errorCode, boost::asio::ip::tcp::socket socket)
{
    if (errorCode) {
        std::stringstream ss;
        ss << "failed to accept connection: error code: " << errorCode.to_string();
        throw std::runtime_error(ss.str());
    }
    else {
        std::make_shared<Session>(std::move(socket))->run();
    }

    doAccept();
}

WebsocketServer::Session::Session(boost::asio::ip::tcp::socket&& socket) :
    std::enable_shared_from_this<WebsocketServer::Session>(),
    ws(std::move(socket))
{
}

void WebsocketServer::Session::run()
{
    boost::asio::dispatch(
        ws.get_executor(),
        boost::beast::bind_front_handler(&WebsocketServer::Session::onRun, shared_from_this()));
}

void WebsocketServer::Session::onRun()
{
    ws.set_option(boost::beast::websocket::stream_base::timeout::suggested(boost::beast::role_type::server));
    ws.async_accept(boost::beast::bind_front_handler(&WebsocketServer::Session::onAccept, shared_from_this()));
}

void WebsocketServer::Session::onAccept(boost::beast::error_code errorCode)
{
    if (errorCode) {
        std::stringstream ss;
        ss << "failed to accept session: error code: " << errorCode.to_string();
        throw std::runtime_error(ss.str());
    }

    doRead();
}

void WebsocketServer::Session::doRead()
{
    ws.async_read(buffer, boost::beast::bind_front_handler(&WebsocketServer::Session::onRead, shared_from_this()));
}

void WebsocketServer::Session::onRead(boost::beast::error_code errorCode, std::size_t bytesTransferred)
{
    if (errorCode == boost::beast::websocket::error::closed) {
        return;
    }

    if (errorCode) {
        std::stringstream ss;
        ss << "failed to read: error code: " << errorCode.to_string();
        throw std::runtime_error(ss.str());
    }

    // TODO: Actual logic
    ws.text(ws.got_text());
    ws.async_write(
        buffer.data(),
        boost::beast::bind_front_handler(&WebsocketServer::Session::onWrite, shared_from_this()));
}

void WebsocketServer::Session::onWrite(boost::beast::error_code errorCode, std::size_t bytesTransferred)
{
    if (errorCode) {
        std::stringstream ss;
        ss << "failed to write: error code: " << errorCode.to_string();
        throw std::runtime_error(ss.str());
    }

    // TODO: Actual logic
    buffer.consume(buffer.size());
    doRead();
}

}
