# Trabalho SSC0640 Sistemas Operacionais
## <center>Linux Kernel Module
&nbsp;
<table>
<tr>
    <td align="center">
        <a href="https://github.com/Guichiarotto">
            <img src="https://avatars.githubusercontent.com/u/110139874?v=4" width="150;" alt="Guichiarotto"/>
            <br />
            <sub><b>Guilherme Chiarotto De Moraes</b></sub>
            <br />
            <sub>12745229</sub>
        </a>
    </td>
    <td align="center">
        <a href="https://github.com/briotisk">
            <img src="https://avatars.githubusercontent.com/u/86500240?v=4" width="150;" alt="briotisk"/>
            <br />
            <sub><b>Gabriel Henrique Brioto</b></sub>
            <br />
            <sub>12547764</sub>
        </a>
    </td>
    <td align="center">
        <a href="https://github.com/Dauboau">
            <img src="https://avatars.githubusercontent.com/u/86164187?v=4" width="150;" alt="Dauboau"/>
            <br />
            <sub><b>Daniel Contente Romanzini</b></sub>
            <br />
            <sub>12547614</sub>
        </a>
    </td>
</tr>
</table>

# Introdução
<p style="text-align: justify;">Este trabalho tem como objetivo de desenvolver um módulo de kernel do Linux que implementa um backdoor keylogger. Ele registra um dispositivo de entrada para capturar eventos do teclado, armazena as teclas digitadas em um buffer e envia esses dados por meio de um socket para um servidor, tendo como finalidade guardar e visualizar o conteúdo que foi coletado.</p>

&nbsp;
# Descrição das principais funções do código fonte

## Arquivo mymodule.c
* Função static void stop_server(void)
<p style="text-align: justify;">Esta função é responsável por liberar os recursos relacionados ao socket do servidor.</p>
&nbsp;

* Função static int start_server(void)
<p style="text-align: justify;">Esta função é responsável por criar um socket, vinculá-lo a um endereço IP e porta específicos, ouvir por conexões de entrada e aceitar uma conexão do cliente.</p>
&nbsp;

* Função static int send_msg(void)
<p style="text-align: justify;">Esta função é responsável por enviar a mensagem contida no buffer para o cliente conectado por meio do socket.</p>
&nbsp;

* Funcão static int keylogger_notify(struct notifier_block *self, unsigned long event, void *data)
<p style="text-align: justify;">Esta é uma função de callback registrada como um notifier para capturar eventos do teclado. Ela é chamada sempre que uma tecla é pressionada. Ela relata a tecla pressionada ao dispositivo de entrada e armazena o valor da tecla no buffer. Quando o buffer está cheio, ele é enviado para o cliente.</p>
&nbsp;

* Funcão static int start_keylogger(void)
<p style="text-align: justify;">Esta função é responsável por alocar e registrar um dispositivo de entrada para capturar eventos do teclado.</p>
&nbsp;

* Função static void stop_keylogger(void)
<p style="text-align: justify;">Esta função é responsável por liberar os recursos relacionados ao keylogger, como o dispositivo de entrada e o notifier.</p>
&nbsp;

* Função static int __init keylogger_init(void)
<p style="text-align: justify;">Esta é a função de inicialização do módulo. Ela registra o keylogger, inicia o servidor e retorna 0 se todas as operações forem bem-sucedidas.</p>
&nbsp;

* Função static void __exit keylogger_exit(void)
<p style="text-align: justify;">Esta é a função de saída do módulo. Ela para o keylogger e o servidor.</p>
&nbsp;

## Arquivo client.c
* Função socket()
<p style="text-align: justify;">Cria um socket para comunicação.</p>
&nbsp;

* Função connect()
<p style="text-align: justify;">Estabelece uma conexão com o servidor usando o socket.</p>
&nbsp;

* Função MQTTClient_create()
<p style="text-align: justify;">O MQTTé um protocolo de mensagens leve, projetado para comunicação entre dispositivos em redes de sensores e ambientes de IoT. Esta função inicializa a estrutura do cliente MQTT.</p>
&nbsp;

* Função MQTTClient_connect()
<p style="text-align: justify;">Conecta o cliente MQTT ao broker MQTT especificado.</p>
&nbsp;

* Loop principal
```c
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
```
<p style="text-align: justify;">Esse loop vai ler as mensagens recebidas do servidor usando read() e verifica se a mensagem é vazia ou não. Após isso, constrói uma mensagem JSON com base na mensagem recebida, que a mesma é então publicada no tópico MQTT usando MQTTClient_publishMessage(). A mensagem também é printada no console.</p>
&nbsp;

## IBM Watson IoT Platform

As mensagens publicadas através do protocolo MQTT são recebidas pela plataforma no servidor US-South em Dallas, que faz parte da IBM Cloud, permitindo a visualização das mensagens, armazenamento de histórico, visualização da quantidade de dados transmitidos e interação com APIs externas.
&nbsp;

# Orientações para execução do código

* Compilação e Execução
<p style="text-align: justify;">Primeiramente é preciso compilar o módulo que está no arquivo mymodule.c. Para isso, basta estar com todos os arquivos e executar:</p>

```c
$ make
```

<p style="text-align: justify;">Após isso, compile o client.c executando:</p>

```c
$ gcc client.c -o client
```

<p style="text-align: justify;">Carregue o módulo com:</p>

```c
$ sudo insmod mymodule.ko
```

<p style="text-align: justify;">Por fim, execute o cliente em um novo terminal com o comando:</p>

```c
$ ./client
```

<p style="text-align: justify;">Para descarregar o módulo e encerrar a conexão, execute o seguinte comando:</p>

```c
$ sudo rmmod mymodule.ko
```

&nbsp;
