# Casos de Uso Detalhados para o Mini-Shell

## Exemplos de Comandos Testados e Suas Saídas

O mini-shell suporta a execução de comandos built-in e externos, além de redirecionamento de I/O e pipes.

### Comandos Built-in

*   `exit`:
    ```
    🐚/home/ubuntu🐚$> exit
    Shutting down...
    [===========💥]
    ✅ EXIT ✅
    ```
    Encerra o mini-shell com uma animação de desligamento.

*   `env`:
    ```
    🐚/home/ubuntu🐚$> env
    TERM=xterm
    PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
    LANG=C.UTF-8
    ... (outras variáveis de ambiente)
    ```
    Exibe as variáveis de ambiente do processo atual.

*   `echo <texto>`:
    ```
    🐚/home/ubuntu🐚$> echo Hello World
    Hello World
    🐚/home/ubuntu🐚$> echo -n Hello World
    Hello World🐚/home/ubuntu🐚$>
    ```
    Imprime o texto fornecido. A opção `-n` suprime a nova linha final.

### Comandos Externos

O mini-shell pode executar qualquer comando disponível no `PATH` do sistema.

*   `ls`:
    ```
    🐚/home/ubuntu🐚$> ls
    builtin.c  index.c  index.h  mini_shell  utils.c
    🐚/home/ubuntu🐚$> ls -l
    total 60
    -rw-r--r-- 1 ubuntu ubuntu  3028 Jun 16 10:00 builtin.c
    -rw-r--r-- 1 ubuntu ubuntu  5820 Jun 16 10:00 index.c
    -rw-r--r-- 1 ubuntu ubuntu  1292 Jun 16 10:00 index.h
    -rwxr-xr-x 1 ubuntu ubuntu 17264 Jun 16 10:00 mini_shell
    -rw-r--r-- 1 ubuntu ubuntu  3568 Jun 16 10:00 utils.c
    ```
    Lista o conteúdo do diretório atual.

*   `cat <arquivo>`:
    ```bash
    🐚/home/ubuntu🐚$> cat builtin.c
    #include "index.h"
    #include <stdbool.h>

    int index_exit(char **args){
    ...
    ```
    Exibe o conteúdo de um arquivo.


"Hello World" > output.txt
    🐚/home/ubuntu🐚$> cat output.txt
    Hello World
    ```

*   **Redirecionamento de Saída (Append `>>`):** Redireciona a saída padrão de um comando para um arquivo, adicionando ao final.
    ```bash
    🐚/home/ubuntu🐚$> echo "First line" > append.txt
    🐚/home/ubuntu🐚$> echo "Second line" >> append.txt
    🐚/home/ubuntu🐚$> cat append.txt
    First line
    Second line
    ```
