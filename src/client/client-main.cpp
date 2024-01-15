// client-main.cpp

#include <client/client-main.hpp>
#include <common/utils.hpp>

int main() {
    Utils::printMessage("CLIENT", "Client starting...");

    TCPClient client("127.0.0.1", 8080);
    client.sendData("Hello, Server!");
    client.receiveData();

    Utils::printMessage("CLIENT", "Client closing...");

    return 0;
}
