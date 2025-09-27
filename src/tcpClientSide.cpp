#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket.\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8000);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported.\n";
        close(clientSocket);
        return 1;
    }

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        std::cerr << "Connection failed.\n";
        close(clientSocket);
        return 1;
    }

    const char* message = "Hello, server!";
    if (send(clientSocket, message, strlen(message), 0) == -1) {
        std::cerr << "Failed to send message.\n";
        close(clientSocket);
        return 1;
    }

    std::cout << "Message sent to server.\n";

    close(clientSocket);
    return 0;
}
