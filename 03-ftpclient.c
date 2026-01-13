#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    FILE *fp;
    int csd, n, s, cport;
    char name[100], rcvg[100], fname[100];
    struct sockaddr_in servaddr;

    printf("Enter the port: ");
    scanf("%d", &cport);

    // Create socket
    csd = socket(AF_INET, SOCK_STREAM, 0);
    if (csd < 0) {
        printf("Error creating socket\n");
        exit(0);
    } else {
        printf("Socket is created\n");
    }

    // Server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(cport);

    // Connect to server
    if (connect(csd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        printf("Error in connection\n");
    else
        printf("Connected to server\n");

    // File names
    printf("Enter the existing file name: ");
    scanf("%s", name);

    printf("Enter the new file name: ");
    scanf("%s", fname);

    fp = fopen(fname, "w");

    // Send filename to server
    send(csd, name, sizeof(name), 0);

    // Receive file contents
    while (1) {
        bzero(rcvg, 100);
        s = recv(csd, rcvg, 100, 0);
        rcvg[s] = '\0';

        if (strcmp(rcvg, "error") == 0) {
            printf("File is not available\n");
            break;
        }

        if (strcmp(rcvg, "completed") == 0) {
            printf("File is transferred successfully\n");
            fclose(fp);
            close(csd);
            break;
        }

        printf("%s", rcvg);
        fprintf(fp, "%s", rcvg);
    }

    return 0;
}
