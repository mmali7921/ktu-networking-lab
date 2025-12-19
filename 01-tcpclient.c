#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2020);
    serverAddr.sin_addr.s_addr = inet_addr("172.18.100.10");
    memset(serverAddr.sin_zero, 0, sizeof(serverAddr.sin_zero));

    addr_size = sizeof(serverAddr);
    connect(clientSocket, (struct sockaddr*) &serverAddr, addr_size);

    while (1) {
        printf("Type a sentence to send to server:\n");
        fgets(buffer, 1024, stdin);
        printf("You typed: %s\n", buffer);
        send(clientSocket, buffer, 1024, 0);
    }

    return 0;
}
