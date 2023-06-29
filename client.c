#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 32

int main() {
    
    int clientSocket, valread;
    struct sockaddr_in serverAddress;
    char *serverIP = "127.0.0.1";
    char message[BUFFER_SIZE] = {0};

    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {

        perror("Socket creation failed");
        exit(EXIT_FAILURE);

    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    if (inet_pton(AF_INET, serverIP, &serverAddress.sin_addr) <= 0) {

        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);

    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {

        perror("Connection failed");
        exit(EXIT_FAILURE);

    }

    while (1) {

        memset(message, 0, sizeof(message));

        valread = read(clientSocket, message, BUFFER_SIZE);
        if(valread != BUFFER_SIZE)
            break;

        if(!strcmp(message, ""))
            continue;
        
        printf("%s\n", message);

    }

    printf("Connection lost\n");

    close(clientSocket);

    return 0;
}
