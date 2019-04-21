//Creating a listener to launch the sessions

#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "beast.hpp"
#include "net.hpp"
#include <boost/smart_ptr.hpp>
#include <memory>
#include <string>

//Forward decalaration
class shared_state;
//Accepts incoming connections and launches the sessions
class listener : public boost::enable_shared_from_this<listener> 
{
public:
    listener(
        net::io_context& ioc,
        tcp::endpoint endpoint,
        boost::shared_ptr<shared_state> const& state);

    //Start accepting incoming connections
    void run();

private:
    net::io_context& ioc_;
    tcp::acceptor acceptor_;
    boost::shared_ptr<shared_state> state_;

    void fail(beast::error_code ec,char const* what);
    void on_accept(beast::error_code ec,tcp::socket socket);
};

#endif