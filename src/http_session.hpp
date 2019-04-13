//Declaring http session

#ifndef HTTP_SESSION_HPP
#define HTTP_SESSION_HPP

#include "net.hpp"
#include "beast.hpp"
#include "shared_state.hpp"
#include <cstdlib>
#include <memory>

/* Represents an established HTTP connection
*/

class http_session : public std::enable_shared_from_this<http_session>
{
public:
    http_session(
        tcp::socket socket,
        std::shared_ptr<shared_state> const& state);

    void run();    
private:
    tcp::socket socket_;
    beast::flat_buffer buffer_;
    std::shared_ptr<shared_state> state_;
    http::request<http::string_body> req_;

    void fail(error_code ec, char const* what);
    void on_read(error_code ec, std::size_t);
    void on_write(
        error_code ec, std::size_t, bool close);
};

#endif