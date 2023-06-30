#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <MQTTClient.h>

#define MQTT_HOST "c3dsew.messaging.internetofthings.ibmcloud.com"
#define MQTT_PORT 1883
#define MQTT_DEVICEID "d:c3dsew:keyboard:12547614"
#define MQTT_USER "use-token-auth"
#define MQTT_TOKEN "BVB9KW1Qy1JKmOoZ9x"
#define MQTT_TOPIC "iot-2/evt/status/fmt/json"
#define MQTT_TOPIC_DISPLAY "iot-2/cmd/display/fmt/json"

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

    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, MQTT_HOST, MQTT_DEVICEID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    conn_opts.keepAliveInterval = 3600;
    conn_opts.cleansession = 1;
    conn_opts.username = MQTT_USER;
    conn_opts.password = MQTT_TOKEN;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect to the MQTT broker, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    char dataJson[1024];
    char json1[] = "{\"data\": \"";
    char json2[] = "\"}";
    while (1) {

        memset(message, 0, sizeof(message));

        valread = read(clientSocket, message, BUFFER_SIZE);
        if(valread != BUFFER_SIZE){
            break;
        }

        if(!strcmp(message, "")){
            continue;
        }

        dataJson[strcspn(dataJson, "\r\n")] = 0;
        strcpy(dataJson, json1);
        strcat(dataJson, message);
        strcat(dataJson, json2);

        pubmsg.payload = dataJson;
        pubmsg.payloadlen = strlen(dataJson);
        pubmsg.qos = 0;
        pubmsg.retained = 0;
        MQTTClient_publishMessage(client, MQTT_TOPIC, &pubmsg, &token);
        
        printf("%s\n", message);

    }

    printf("Connection lost\n");

    close(clientSocket);

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    return 0;
}
