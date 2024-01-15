// tcp-client.hpp

#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <iostream>
#include <string>

class TCPClient {
public:
    TCPClient(const std::string& serverAddress, int port);
    void connectServer();
    void sendData(const std::string& data);
    void receiveData();
    ~TCPClient();

private:
    std::string serverAddress;
    int port;
    int clientSocket;
};

#endif // TCP_CLIENT_HPP
