// tcp-server.hpp

#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <iostream>
#include <string>

class TCPServer {
public:
    TCPServer(int port);
    void start();
    ~TCPServer();

private:
    int port;
    int serverSocket;

    void initialize();
};

#endif // TCP_SERVER_HPP
