//Boost chat server
#include "listener.hpp"
#include "shared_state.hpp"
#include <boost/asio/signal_set.hpp>
#include <iostream>

int main(int argc,char* argv[])
{
    if(argc!=4)
    {
        std::cerr << "Usage: websocket-chat-server <address> <port> <doc_root>\n" << 
                    "Example:\n" <<
                    "   websocket-chat-server 0.0.0.0 8080 . \n";
        return EXIT_FAILURE;
    }
    auto address = net::ip::make_address(argv[1]);
    auto port = static_cast<unsigned short>(std::atoi(argv[2]));
    auto doc_root = argv[3];

    //The io_context is required form all I/O
    net::io_context ioc;
    
    //Create and launch a listening port
    std::make_shared<listener>
            (ioc,
            tcp::endpoint{address,port},
            std::make_shared<shared_state>(doc_root))->run();
    
    //Capture SIGINT and SIGTERM to perform a clean shutdown
    net::signal_set signals(ioc,SIGINT,SIGTERM);
    signals.async_wait(
        [&ioc](boost::system::error_code const&, int)
        {
            //Stop the io_context. This will cause run()
            //to return immediately, eventually destorying the
            //io_context and any remainging handlers in it.
            ioc.stop();
        });

    //RUN the I/O service on the main thread
    ioc.run();            

    return EXIT_SUCCESS;
}