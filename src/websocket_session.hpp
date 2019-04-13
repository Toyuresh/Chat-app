//Creating session 

#ifndef WEBSOCKET_SESSION_HPP
#define WEBSOCKET_SESSION_HPP

#include "net.hpp"
#include "beast.hpp"
#include "shared_state.hpp"

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

//Forward declaration
class shared_state;

//Represents an active websocket connection to the server

class websocket_session : public std::enable_shared_from_this<websocket_session>
{

public:
    websocket_session(tcp::socket socket,std::shared_ptr<shared_state>const& state);
    ~websocket_session();

    template<class Body,class Allocator>
    void run(http::request<Body,http::basic_fields<Allocator>>req);

    //Send a message
    void send(std::shared_ptr<std::string const>const& ss);

private:
    beast::flat_buffer buffer_;
    websocket::stream<tcp::socket> ws_;
    std::shared_ptr<shared_state> state_;
    std::vector<std::shared_ptr<std::string const>> queue_;

    void fail(error_code ec,char const* what);
    void on_accept(error_code ec);
    void on_read(error_code ec, std::size_t bytes_transferred);
    void on_write(error_code ec,std::size_t bytes_transferred);
};

template<class Body,class Allocator>
void
websocket_session::run(http::request<Body,http::basic_fields<Allocator>> req)
{
    //Accept the websocket handshake

    ws_.async_accept(req,
                        std::bind(
                            &websocket_session::on_accept,
                            shared_from_this(),
                            std::placeholders::_1
                        ));
}

#endif