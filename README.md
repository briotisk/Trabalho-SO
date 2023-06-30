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
<p style="text-align: justify;"></p>

&nbsp;
# Descrição das principais funções do código fonte

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

# Orientações para execução do código
&nbsp;

* Instalação
<p style="text-align: justify;"></p>

```c
NÃO SEI
```

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
