#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int serverSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;

    // 1. Create UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Fill server address details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2563);
    serverAddr.sin_addr.s_addr = inet_addr("172.18.100.10");
    memset(serverAddr.sin_zero, 0, sizeof(serverAddr.sin_zero));

    // 3. Bind socket to IP and port
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    printf("UDP Server waiting for messages...\n");

    addr_size = sizeof(clientAddr);

    // 4. Receive data from client
    while (1) {
        recvfrom(serverSocket, buffer, 1024, 0,
                 (struct sockaddr*)&clientAddr, &addr_size);

        printf("Message from client: %s\n", buffer);
    }

    close(serverSocket);
    return 0;
}
