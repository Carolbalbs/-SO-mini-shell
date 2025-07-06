# Mini-Shell 

Este projeto implementa um mini-shell básico em C, simulando funcionalidades de um interpretador de comandos Linux. Ele foi desenvolvido como parte de um projeto integrador para explorar chamadas de sistema e conceitos fundamentais de sistemas operacionais.

## Como Compilar e Rodar

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

## Chamadas ao Sistema Utilizadas

O mini-shell faz uso extensivo das seguintes chamadas de sistema POSIX para sua operação:

*   `fork()`: Utilizada para criar novos processos filhos, permitindo a execução de comandos externos sem encerrar o shell principal.
*   `execvp()`: Usada pelo processo filho para substituir sua imagem pelo programa do comando digitado. A função procura o executável no `PATH` do sistema.
*   `wait()`: Empregada pelo processo pai para aguardar a conclusão de um processo filho, coletando seu status de saída e evitando processos zumbis.
*   `read()`: Implementada para ler a entrada do usuário do `stdin`, conforme o requisito do projeto.
*   `write()`: Utilizada para exibir o prompt e outras mensagens na saída padrão (`stdout`) e erro padrão (`stderr`), conforme o requisito do projeto.
*   `open()`: Usada para abrir arquivos para operações de redirecionamento de entrada e saída.
*   `dup2()`: Essencial para implementar o redirecionamento de entrada/saída e pipes, duplicando descritores de arquivo.
*   `pipe()`: Utilizada para criar um pipe de comunicação entre processos, fundamental para a funcionalidade de pipes.
*   `getcwd()`: Obtém o diretório de trabalho atual para exibir no prompt.
*   `malloc()` e `realloc()`: Embora não sejam chamadas de sistema diretamente, são funções de gerenciamento de memória de baixo nível que interagem com o sistema para alocar e realocar memória dinamicamente.

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

### Redirecionamento de Entrada/Saída

*   **Redirecionamento de Saída (`>`):** Redireciona a saída padrão de um comando para um arquivo, sobrescrevendo-o.
    ```bash
    🐚/home/ubuntu🐚$> echo 


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

*   **Redirecionamento de Entrada (`<`):** Redireciona a entrada padrão de um comando de um arquivo.
    ```bash
    🐚/home/ubuntu🐚$> cat < append.txt
    First line
    Second line
    ```

### Pipes

O mini-shell suporta pipes (`|`) para encadear comandos, onde a saída de um comando se torna a entrada do próximo.

*   **Exemplo de Pipe:**
    ```bash
    🐚/home/ubuntu🐚$> ls -l | grep mini_shell
    -rwxr-xr-x 1 ubuntu ubuntu 17264 Jun 16 10:00 mini_shell
    ```
    Lista os arquivos detalhadamente e filtra a linha que contém "mini_shell".

## Limitações Conhecidas da Implementação

Esta versão do mini-shell possui algumas limitações:

*   **Comandos Built-in Fixos**: A lista de comandos built-in (`env`, `exit`, `echo`) é fixa e não pode ser estendida dinamicamente em tempo de execução.
*   **Ausência de Variáveis de Ambiente do Shell**: Não há suporte para variáveis de ambiente internas do shell (ex: `$PATH`, `$HOME`) que podem ser definidas e usadas dentro do shell.
*   **Sem Histórico de Comandos**: Não há funcionalidade de histórico de comandos (setas para cima/baixo).
*   **Sem Autocompletar**: Não há suporte para autocompletar nomes de arquivos ou comandos.
*   **Tratamento Básico de Erros**: Embora `perror` seja usado para erros de chamadas de sistema, o tratamento de erros para comandos não encontrados é genérico ("Command not found") e não fornece detalhes específicos sobre o motivo da falha (ex: permissão negada, comando inexistente).
*   **Ausência de Comandos Complexos**: Não há suporte para estruturas de controle de fluxo (if, for, while), execução em segundo plano (`&`), ou encadeamento de comandos com `&&` ou `||`.
*   **Gerenciamento de Jobs**: Não há suporte para gerenciamento de jobs (suspender, retomar processos).

## Vídeo Curto Demonstrando o Uso do Shell

Para uma demonstração visual do mini-shell em ação, por favor, assista ao vídeo disponível em [Link para o Vídeo] (a ser fornecido pelo usuário, pois a ferramenta não gera vídeos).




## Funcionalidades Implementadas

### Parsing Robusto (Tratamento de Aspas)

O shell agora suporta o parsing de argumentos que contêm espaços, utilizando aspas simples (`'`) ou duplas (`"`). Isso permite que comandos como `echo "Hello World"` sejam interpretados corretamente como um único argumento. A função `split_line_with_quotes` é responsável por essa lógica, garantindo que o texto dentro das aspas seja tratado como um token único, mesmo que contenha delimitadores de espaço.

### Uso de `read()` e `write()`

Para maior controle sobre as operações de entrada e saída, o shell foi modificado para utilizar as chamadas de sistema `read()` e `write()` diretamente. A função `read_line_from_fd` em `utils.c` lê a entrada caractere por caractere de um descritor de arquivo (`fd`), permitindo a leitura de linhas de forma mais flexível. Similarmente, a saída do prompt é agora gerenciada por `write()` em `index_read_line`, proporcionando uma interação mais direta com o terminal.

### Tratamento de Erro "Comando Não Encontrado"

Quando um comando externo não é encontrado no PATH do sistema, o shell agora exibe uma mensagem de erro clara: "Command not found". Isso é implementado na função `Execvp` em `utils.c`, que verifica o retorno de `execvp` e, em caso de falha, imprime a mensagem de erro apropriada no `stderr` antes de retornar um status de erro. Isso melhora a experiência do usuário, fornecendo feedback imediato sobre comandos inválidos.

### Redirecionamento de Entrada/Saída

O mini-shell agora suporta redirecionamento de entrada (`<`), redirecionamento de saída para sobrescrever (`>`) e redirecionamento de saída para anexar (`>>`). A função `handle_redirection` em `index.c` é responsável por identificar esses operadores na linha de comando, abrir os arquivos correspondentes e duplicar os descritores de arquivo (`dup2`) para redirecionar `stdin` ou `stdout` conforme necessário. Após a execução do comando, os descritores de arquivo originais são restaurados para garantir o comportamento normal do shell.

Exemplos:
- `cat < input.txt`: Redireciona o conteúdo de `input.txt` para a entrada do comando `cat`.
- `echo "Hello" > output.txt`: Escreve "Hello" no arquivo `output.txt`, sobrescrevendo o conteúdo existente.
- `echo "World" >> output.txt`: Anexa "World" ao final do arquivo `output.txt`.

### Pipes (`|`)

O shell agora permite a comunicação entre comandos através de pipes. Múltiplos comandos podem ser encadeados usando o operador `|`, onde a saída de um comando se torna a entrada do próximo. A função `execute_pipeline` em `index.c` gerencia a criação de pipes (`pipe()`), a duplicação de descritores de arquivo e a execução de processos filhos para cada comando na pipeline, garantindo que o fluxo de dados seja correto.

Exemplo:
- `ls -l | grep .c`: Lista todos os arquivos no diretório atual e filtra aqueles que terminam com `.c`.

### Built-in `cd`

O comando `cd` (change directory) foi implementado como um built-in do shell. Isso significa que a mudança de diretório é tratada diretamente pelo shell, sem a necessidade de invocar um processo externo. A função `index_cd` em `builtin.c` utiliza a chamada de sistema `chdir()` para alterar o diretório de trabalho atual do shell. Se nenhum argumento for fornecido, o `cd` muda para o diretório `HOME` do usuário. Em caso de erro (por exemplo, diretório não encontrado), uma mensagem de erro é exibida.

Exemplos:
- `cd /tmp`: Muda para o diretório `/tmp`.
- `cd`: Muda para o diretório `HOME` do usuário.
- `cd non_existent_dir`: Exibe uma mensagem de erro.


