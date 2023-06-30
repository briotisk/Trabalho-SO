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
# Descrição das principais funções do código

* Função 1
```c

```
<p style="text-align: justify;"></p>
<p style="text-align: justify;"></p>
<p style="text-align: justify;"></p>
<p style="text-align: justify;"></p>
<p style="text-align: justify;"></p>
&nbsp;

* Função 2
```c

```
<p style="text-align: justify;"></p>
&nbsp;

* Funcão 3
```c

```
<p style="text-align: justify;"></p>
&nbsp;

* Funcão 4
```c

```
<p style="text-align: justify;"></p>
&nbsp;

* Função 5
```c

```
<p style="text-align: justify;"></p>
&nbsp;

* Função 6
```c

```
<p style="text-align: justify;"></p>
&nbsp;

# Orientações para execução do código
<p style="text-align: justify;"></p>
&nbsp;

* Instalação
<p style="text-align: justify;"></p>

```c

```
&nbsp;

* Compilação e Execução
<p style="text-align: justify;">Primeiramente é preciso compilar o módulo que está no arquivo mymodule.c</p>
<p style="text-align: justify;">Para isso, basta estar com todos os arquivos e executar:</p>

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
