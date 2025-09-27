#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Socket creation failed.\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddress.sin_zero, 0, sizeof serverAddress.sin_zero);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Bind failed.\n";
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 2) < 0) {
        std::cerr << "Listen failed.\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "Server listening on port 8000...\n";

    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket < 0) {
        std::cerr << "Accept failed.\n";
        close(serverSocket);
        return 1;
    }

    char buffer[1024] = {0};
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived < 0) {
        std::cerr << "Receive failed.\n";
    } else {
        buffer[bytesReceived] = '\0'; // Null-terminate the string
        std::cout << "Message from client: " << buffer << std::endl;
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}
