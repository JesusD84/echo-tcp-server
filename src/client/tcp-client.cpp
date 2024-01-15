// tcp-client.cpp

#include <client/tcp-client.hpp>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

TCPClient::TCPClient(const std::string& serverAddress, int port)
    : serverAddress(serverAddress), port(port), clientSocket(-1) {
    connectServer();
}

void TCPClient::connectServer() {
    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Prepare the sockaddr_in structure
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, serverAddress.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address/Address not supported" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected to the server" << std::endl;
}

void TCPClient::sendData(const std::string& data) {
    // Send data to the server
    write(clientSocket, data.c_str(), data.size());
    std::cout << "Data sent to server: " << data << std::endl;
}

void TCPClient::receiveData() {
    // Receive data from the server
    char buffer[1024];
    int bytesRead = read(clientSocket, buffer, sizeof(buffer));

    if (bytesRead > 0) {
        std::cout << "Data received from server: " << std::string(buffer, bytesRead) << std::endl;
    } else if (bytesRead == 0) {
        std::cout << "Server disconnected" << std::endl;
    } else {
        std::cerr << "Error reading from server" << std::endl;
    }
}

TCPClient::~TCPClient() {
    // Close the socket
    close(clientSocket);
}
