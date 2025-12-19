#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    // 1. Create UDP socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Fill server address details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2563);
    serverAddr.sin_addr.s_addr = inet_addr("172.18.100.10");
    memset(serverAddr.sin_zero, 0, sizeof(serverAddr.sin_zero));

    addr_size = sizeof(serverAddr);

    // 3. Send data to server
    while (1) {
        printf("Enter message to send:\n");
        fgets(buffer, 1024, stdin);

        sendto(clientSocket, buffer, strlen(buffer), 0,
               (struct sockaddr*)&serverAddr, addr_size);
    }

    close(clientSocket);
    return 0;
}

