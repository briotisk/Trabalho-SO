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
    char buffer[BUFFER_SIZE] = {0};

    // Criação do socket do cliente
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    // Converte o endereço IP de string para formato binário
    if (inet_pton(AF_INET, serverIP, &serverAddress.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Conecta-se ao servidor remoto
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    while (1) {

        // Limpa o buffer de resposta
        memset(buffer, 0, sizeof(buffer));

        // Lê a resposta do servidor
        valread = read(clientSocket, buffer, BUFFER_SIZE);
        if(valread != BUFFER_SIZE)
            break;

        //verifica se de fato há uma mensagem nova
        if(!strcmp(buffer, ""))
            continue;
        
        printf("%s\n", buffer);

    }

    printf("Connection lost\n");

    // Fecha o socket do cliente
    close(clientSocket);

    return 0;
}
