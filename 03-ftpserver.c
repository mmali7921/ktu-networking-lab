#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    FILE *fp;
    int sd, newsd, n, a, bd, port, clilen;
    char fileread[100], rcv[100];
    struct sockaddr_in servaddr, cliaddr;

    printf("Enter the port address\n");
    scanf("%d", &port);

    // Create socket
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
        printf("Can't create socket\n");
    else
        printf("Socket is created\n");

    // Server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    a = sizeof(servaddr);

    // Bind
    bd = bind(sd, (struct sockaddr *)&servaddr, a);
    if (bd < 0)
        printf("Can't bind\n");
    else
        printf("Binded\n");

    // Listen
    listen(sd, 5);

    // Accept
    clilen = sizeof(cliaddr);
    newsd = accept(sd, (struct sockaddr *)&cliaddr, &clilen);
    if (newsd < 0)
        printf("Can't accept\n");
    else
        printf("Accepted\n");

    // Receive filename
    n = recv(newsd, rcv, 100, 0);
    rcv[n] = '\0';

    // Open file
    fp = fopen(rcv, "r");
    if (fp == NULL) {
        send(newsd, "error", 5, 0);
        close(newsd);
    } else {
        // Send file contents
        while (fgets(fileread, sizeof(fileread), fp)) {
            if (send(newsd, fileread, sizeof(fileread), 0) < 0)
                printf("Can't send file contents\n");
        }
        sleep(1);
        fclose(fp);
    }

    send(newsd, "completed", 9, 0);
    close(newsd);
    close(sd);

    return 0;
}
