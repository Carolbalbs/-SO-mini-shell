# Como Compilar e Rodar

Para compilar o mini-shell, certifique-se de ter o `gcc` (GNU Compiler Collection) instalado em seu sistema. Em sistemas baseados em Debian/Ubuntu, você pode instalá-lo com:

```bash
sudo apt-get update
sudo apt-get install build-essential
```

Após a instalação do `gcc`, navegue até o diretório onde os arquivos-fonte (`index.c`, `utils.c`, `builtin.c`, `index.h`) estão localizados e execute o seguinte comando para compilar:

```bash
gcc -o mini_shell index.c utils.c builtin.c -I.
```

Este comando criará um executável chamado `mini_shell` no diretório atual.

Para rodar o mini-shell, basta executar o binário:

```bash
./mini_shell
```

O shell exibirá um prompt interativo (`🐚/caminho/atual🐚$>`) onde você poderá digitar comandos.


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


## Vídeo Curto Demonstrando o Uso do Shell

Mini-shell em ação! Vídeo disponível em [./] 


## Limitações Conhecidas da Implementação

Esta versão do mini-shell possui algumas limitações:

*   **Comandos Built-in Fixos**: A lista de comandos built-in (`env`, `exit`, `echo`) é fixa e não pode ser estendida dinamicamente em tempo de execução.
*   **Ausência de Variáveis de Ambiente do Shell**: Não há suporte para variáveis de ambiente internas do shell (ex: `$PATH`, `$HOME`) que podem ser definidas e usadas dentro do shell.
*   **Sem Histórico de Comandos**: Não há funcionalidade de histórico de comandos (setas para cima/baixo).
*   **Sem Autocompletar**: Não há suporte para autocompletar nomes de arquivos ou comandos.
*   **Tratamento Básico de Erros**: Embora `perror` seja usado para erros de chamadas de sistema, o tratamento de erros para comandos não encontrados é genérico ("Command not found") e não fornece detalhes específicos sobre o motivo da falha (ex: permissão negada, comando inexistente).
*   **Ausência de Comandos Complexos**: Não há suporte para estruturas de controle de fluxo (if, for, while), execução em segundo plano (`&`), ou encadeamento de comandos com `&&` ou `||`.
*   **Gerenciamento de Jobs**: Não há suporte para gerenciamento de jobs (suspender, retomar processos).




