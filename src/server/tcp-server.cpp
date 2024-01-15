// tcp-server.cpp

#include <server/tcp-server.hpp>
#include <arpa/inet.h>
#include <unistd.h>

TCPServer::TCPServer(int port) : port(port), serverSocket(-1) {
    initialize();
}

void TCPServer::initialize() {
    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Prepare the sockaddr_in structure
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Server initialized on port " << port << std::endl;
}

void TCPServer::start() {
    // Listen for incoming connections
    listen(serverSocket, 3);

    std::cout << "Waiting for incoming connections..." << std::endl;

    // Accept incoming connection
    int clientSocket;
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (clientSocket < 0) {
        std::cerr << "Error accepting connection" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection accepted" << std::endl;

    // Read and echo data
    char buffer[1024];
    int bytesRead;

    while ((bytesRead = read(clientSocket, buffer, sizeof(buffer))) > 0) {
        write(clientSocket, buffer, bytesRead);
    }

    if (bytesRead == 0) {
        std::cout << "Client disconnected" << std::endl;
    } else if (bytesRead < 0) {
        std::cerr << "Error reading from client" << std::endl;
    }

    // Close the socket
    close(clientSocket);
}

TCPServer::~TCPServer() {
    // Close the socket
    close(serverSocket);
}
