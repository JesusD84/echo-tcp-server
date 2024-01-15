// server-main.cpp

#include <server/server-main.hpp>
#include <common/utils.hpp>

int main() {
    Utils::printMessage("SERVER", "Server starting...");

    TCPServer server(8080);
    server.start();

    Utils::printMessage("SERVER", "Server closing...");
    return 0;
}
