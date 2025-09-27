#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

int main() {
    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket.\n";
        return 1;
    }

    // Setup server address
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8000);

    // Convert IP string to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported.\n";
        close(clientSocket);
        return 1;
    }

    // Connect to the server
    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        std::cerr << "Connection failed.\n";
        close(clientSocket);
        return 1;
    }

    // Send message
    const char* message = "Hello, server!";
    if (send(clientSocket, message, strlen(message), 0) == -1) {
        std::cerr << "Failed to send message.\n";
        close(clientSocket);
        return 1;
    }

    std::cout << "Message sent to server.\n";

    // Close socket
    close(clientSocket);
    return 0;
}
