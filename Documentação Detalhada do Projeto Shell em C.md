# Documentação Detalhada do Projeto Shell em C

## Introdução

Este documento fornece uma análise detalhada dos arquivos de código-fonte C que compõem um projeto de shell básico. O projeto é dividido em módulos, cada um com responsabilidades específicas:

*   `index.h`: Arquivo de cabeçalho que contém definições globais, macros e protótipos de funções.
*   `utils.c`: Implementa funções utilitárias e wrappers para chamadas de sistema.
*   `builtin.c`: Contém a implementação de comandos built-in do shell.
*   `index.c`: A lógica principal do shell, incluindo o loop de leitura, avaliação e execução de comandos (REPL).

O objetivo desta documentação é descrever a funcionalidade de cada arquivo, as funções que eles contêm e como interagem para formar o shell completo.




## `index.h` - Arquivo de Cabeçalho Principal

O arquivo `index.h` serve como o cabeçalho central para o projeto do shell, definindo constantes, incluindo bibliotecas padrão, declarando macros e protótipos de funções que são utilizadas em múltiplos arquivos-fonte. Ele estabelece a base para a comunicação e a coerência entre os diferentes módulos do shell.

### Constantes e Códigos de Saída

Este cabeçalho define códigos de saída padrão que são utilizados em todo o projeto para indicar o status de sucesso ou falha de operações. Estes incluem:

*   `EX_OK`: Representa uma saída bem-sucedida, geralmente associada a `EXIT_SUCCESS`.
*   `EX_OSERR`: Indica um erro de sistema operacional, como falha na criação de um processo (`fork`).
*   `EX_UNAVAILABLE`: Sinaliza que um comando ou serviço não está disponível, como uma falha na execução de um programa (`execvp`).

### Inclusões de Bibliotecas Padrão

Para garantir a funcionalidade completa do shell, `index.h` inclui várias bibliotecas padrão do C, que fornecem acesso a funções essenciais para manipulação de entrada/saída, gerenciamento de memória, operações de string e controle de processos:

*   `<stdio.h>`: Para funções de entrada e saída, como `printf` e `getline`.
*   `<stdlib.h>`: Para funções de uso geral, como alocação de memória (`malloc`, `realloc`, `free`) e controle de processos (`exit`).
*   `<unistd.h>`: Para acesso a chamadas de sistema POSIX, como `fork`, `execvp` e `getcwd`.
*   `<string.h>`: Para funções de manipulação de strings, como `strcmp` e `strtok`.
*   `<sys/wait.h>`: Para funções relacionadas ao controle de processos filhos, como `wait` e macros para verificar o status de saída de processos (`WIFEXITED`, `WEXITSTATUS`).

### Macros para Formatação de Saída e Utilitários

O arquivo `index.h` define macros que simplificam a formatação da saída do terminal com cores ANSI e facilitam a impressão de mensagens. Essas macros são cruciais para melhorar a legibilidade e a experiência do usuário no shell:

*   **Cores ANSI**: Macros como `Y` (Amarelo), `G` (Verde), `C` (Ciano), `RED` (Vermelho) e `RST` (Reset) são definidas para aplicar cores ao texto no terminal, tornando as mensagens de status e prompts mais visuais.
*   `p(...)`: Uma macro conveniente que encapsula a função `printf`, permitindo uma sintaxe mais concisa para imprimir mensagens formatadas.
*   `DEL`: Define um conjunto de delimitadores (`\n\t \v\f\r`) usados para tokenizar a entrada do usuário, separando comandos e argumentos.
*   `INDEX_jr`: Uma constante definida como `0`, provavelmente usada para identificar o processo filho após uma chamada `fork`.

### Estruturas de Dados

Uma estrutura fundamental definida em `index.h` é `t_builtin`, que é usada para gerenciar os comandos built-in do shell. Esta estrutura é um array de ponteiros para funções, permitindo que o shell mapeie nomes de comandos para suas respectivas implementações:

```c
typedef struct s_builtin
{
    const char     *builtin_name;
    int (*foo)(char **);
}   t_builtin;
```

*   `builtin_name`: Uma string que armazena o nome do comando built-in (ex: "exit", "env").
*   `foo`: Um ponteiro para uma função que aceita um array de strings (`char **`) como argumentos e retorna um `int`, representando o status de saída do comando.

### Protótipos de Funções

`index.h` declara os protótipos de todas as funções públicas que são implementadas nos arquivos `.c` do projeto. Isso garante que as funções possam ser chamadas de outros arquivos sem problemas de compilação. As funções prototipadas incluem:

*   `printbanner(void)`: Imprime um banner de boas-vindas no início do shell.
*   `spinnerLoading()`: Exibe uma animação de carregamento, geralmente usada antes de sair do shell.
*   `Chdir(const char *path)`: Wrapper para a função `chdir` (não implementada nos arquivos fornecidos, mas prototipada).
*   `Fork(void)`: Wrapper para a função `fork`, para criar um novo processo.
*   `Execvp(const char *file, char *const argv[])`: Wrapper para a função `execvp`, para executar um programa.
*   `Wait(int *status)`: Wrapper para a função `wait`, para aguardar a conclusão de um processo filho.
*   `Wait(pid_t pid, int *status, int options)`: Uma sobrecarga ou declaração duplicada de `Wait`, que pode indicar uma intenção de ter uma função `waitpid` ou um erro de prototipagem.
*   `index_exit(char **)`: Implementação do comando built-in `exit`.
*   `Getcwd(char *, size_t)`: Wrapper para a função `getcwd`, para obter o diretório de trabalho atual.
*   `Malloc(size_t)`: Wrapper para a função `malloc`, para alocação de memória.
*   `Realloc(void *ptr, size_t size)`: Wrapper para a função `realloc`, para realocação de memória.

Em resumo, `index.h` é o ponto de partida para entender a estrutura e as dependências do projeto do shell, fornecendo as definições e declarações necessárias para que os diferentes componentes funcionem em conjunto.




## `utils.c` - Funções Utilitárias e Wrappers de Chamadas de Sistema

O arquivo `utils.c` contém uma coleção de funções utilitárias e wrappers para chamadas de sistema POSIX. Essas funções são projetadas para encapsular a lógica de tratamento de erros das chamadas de sistema subjacentes, tornando o código principal do shell mais limpo e robusto. Em caso de falha, a maioria dessas funções imprime uma mensagem de erro usando `perror` e encerra o programa, garantindo que o shell não continue a operar em um estado inconsistente.

### Wrappers para Gerenciamento de Processos

As funções de gerenciamento de processos em `utils.c` fornecem uma interface segura para operações comuns de processos, como criação, execução e espera:

*   `pid_t Fork(void)`:
    *   **Propósito**: Este é um wrapper para a chamada de sistema `fork()`. Ele cria um novo processo filho que é uma cópia exata do processo pai.
    *   **Comportamento em Erro**: Se `fork()` falhar (retornar um valor negativo), a função imprime uma mensagem de erro (`"Fork Failed"`) usando `perror` e encerra o programa com `exit(EX_OSERR)`. Isso garante que o shell não tente operar com um processo filho que não foi criado corretamente.
    *   **Retorno**: Retorna o ID do processo filho (`pid_t`) para o processo pai e `0` para o processo filho, conforme o comportamento padrão de `fork()`.

*   `void Execvp(const char *file, char *const argv[])`:
    *   **Propósito**: Este wrapper para `execvp()` substitui a imagem do processo atual por um novo programa. Ele procura o executável especificado por `file` nos diretórios listados na variável de ambiente `PATH`.
    *   **Comportamento em Erro**: Antes de chamar `execvp()`, a função verifica se `file` ou `argv` são nulos. Se forem, imprime uma mensagem de erro no `stderr` e encerra com `exit(EXIT_FAILURE)`. Se `execvp()` falhar (retornar `-1`), imprime uma mensagem de erro (`"Failed"`) usando `perror` e encerra o programa com `exit(EX_UNAVAILABLE)`. Isso é crucial porque `execvp()` só retorna em caso de erro; um retorno bem-sucedido significa que o novo programa está em execução.
    *   **Argumentos**: `file` é o nome do programa a ser executado, e `argv` é um array de strings que representa os argumentos da linha de comando para o novo programa, onde `argv[0]` é o nome do programa.

*   `pid_t Wait(int *status)`:
    *   **Propósito**: Este wrapper para `wait()` suspende a execução do processo pai até que um de seus processos filhos termine. Ele é usado para coletar o status de saída de processos filhos e evitar processos zumbis.
    *   **Comportamento em Erro**: A função primeiro verifica se o ponteiro `status` é nulo. Se for, imprime uma mensagem de erro (`"Wait: status argument required"`) e retorna `-1`. Se `wait()` falhar (retornar `-1`), imprime uma mensagem de erro (`"Wait failed"`) usando `perror`. Após a conclusão bem-sucedida de `wait()`, se o processo filho terminou normalmente (`WIFEXITED(*status)`), o status de saída real do filho (`WEXITSTATUS(*status)`) é armazenado em `*status`.
    *   **Retorno**: Retorna o ID do processo filho que terminou ou `-1` em caso de erro.

### Wrappers para Gerenciamento de Memória

As funções de gerenciamento de memória em `utils.c` fornecem alocação e realocação de memória seguras, com tratamento de erros integrado:

*   `void *Malloc(size_t size)`:
    *   **Propósito**: Este wrapper para `malloc()` aloca um bloco de memória do tamanho especificado.
    *   **Comportamento em Erro**: Se `malloc()` falhar (retornar `NULL`), a função imprime uma mensagem de erro (`"Malloc Failed"`) usando `perror` e encerra o programa com `exit(EXIT_FAILURE)`. Um caso especial é quando `size` é `0`, para o qual `Malloc` retorna `NULL` sem erro, seguindo o comportamento comum de `malloc` para alocações de tamanho zero.
    *   **Retorno**: Retorna um ponteiro para o bloco de memória alocado ou `NULL` se `size` for `0`.

*   `void *Realloc(void *ptr, size_t size)`:
    *   **Propósito**: Este wrapper para `realloc()` redimensiona o bloco de memória apontado por `ptr` para o novo `size`.
    *   **Comportamento em Erro**: Se `realloc()` falhar (retornar `NULL`) e o `size` não for `0`, a função imprime uma mensagem de erro (`"Realloc Failed"`) usando `perror` e encerra o programa com `exit(EXIT_FAILURE)`. Se `size` for `0`, `realloc` se comporta como `free(ptr)`, e a função retorna `NULL` sem erro, o que é um comportamento válido.
    *   **Retorno**: Retorna um ponteiro para o bloco de memória redimensionado ou `NULL` se a realocação falhar ou se `size` for `0`.

### Wrappers para Operações de Diretório

`utils.c` inclui um wrapper para obter o diretório de trabalho atual:

*   `void Getcwd(char *buf, size_t size)`:
    *   **Propósito**: Este wrapper para `getcwd()` copia o caminho absoluto do diretório de trabalho atual para o buffer `buf`.
    *   **Comportamento em Erro**: Se `getcwd()` falhar (retornar `NULL`), a função imprime uma mensagem de erro (`"getcwd FAILED"`) usando `perror`.
    *   **Argumentos**: `buf` é o buffer onde o caminho será armazenado, e `size` é o tamanho máximo do buffer.

### Funções de Interface do Usuário

Além dos wrappers, `utils.c` também contém funções para melhorar a experiência do usuário com elementos visuais:

*   `void printbanner(void)`:
    *   **Propósito**: Imprime um banner ASCII art no console. Este banner é exibido no início do shell, fornecendo uma saudação visual.
    *   **Implementação**: Utiliza a macro `p` (que envolve `printf`) e códigos de cores ANSI (definidos em `index.h`) para exibir o banner com formatação colorida.

*   `void spinnerLoading()`:
    *   **Propósito**: Exibe uma animação de "carregamento" ou "desligamento" no console, simulando um processo em andamento antes de o shell ser encerrado.
    *   **Implementação**: A função usa um array de strings (`charging[]`) para representar os diferentes quadros da animação de um spinner. Ela itera sobre esses quadros, imprimindo cada um com um atraso (`usleep`) e forçando a atualização do console (`fflush(stdout)`). No final da animação, imprime uma mensagem de saída e encerra o programa com `exit(X_OK)` (onde `X_OK` é uma constante definida em `index.h` como `EX_OK`).

Em resumo, `utils.c` é um componente vital do shell, fornecendo uma camada de abstração e tratamento de erros para operações de baixo nível, o que contribui significativamente para a robustez e a confiabilidade do sistema.




## `builtin.c` - Implementação de Comandos Built-in

O arquivo `builtin.c` é responsável por implementar os comandos built-in do shell. Comandos built-in são funções que são executadas diretamente pelo shell, em vez de serem programas externos. Isso os torna mais rápidos e eficientes, pois não exigem a criação de um novo processo. Atualmente, este arquivo contém as implementações para os comandos `exit` e `env`.

### `int index_exit(char **args)`

*   **Propósito**: Implementa o comando `exit`, que encerra a execução do shell.
*   **Argumentos**: `char **args` - um array de strings contendo os argumentos passados para o comando `exit`. Embora o protótipo aceite argumentos, a implementação atual não os utiliza (`(void)args;`).
*   **Funcionalidade**: Antes de sair, a função chama `spinnerLoading()`, que exibe uma animação de desligamento, proporcionando uma experiência de usuário mais agradável. Após a animação, o shell é encerrado com `exit(EXIT_SUCCESS)`, indicando uma saída bem-sucedida.
*   **Retorno**: Não retorna, pois a função `exit()` encerra o processo.

### `int index_env(char **args)`

*   **Propósito**: Implementa o comando `env`, que exibe as variáveis de ambiente do processo atual.
*   **Argumentos**: `char **args` - um array de strings contendo os argumentos passados para o comando `env`. A implementação atual não os utiliza (`(void)args;`).
*   **Funcionalidade**: A função acessa a variável global `environ` (declarada como `extern char **environ;`), que é um ponteiro para um array de strings, onde cada string representa uma variável de ambiente no formato `NOME=VALOR`. A função itera sobre este array e imprime cada variável de ambiente em uma nova linha usando a macro `p` (que envolve `printf`).
*   **Comportamento em Erro**: Se `environ` for nulo (o que é improvável em um ambiente POSIX típico, mas é uma verificação de segurança), a função retorna `1`, indicando um erro. Caso contrário, retorna `0` para sucesso.
*   **Retorno**: Retorna `0` em caso de sucesso e `1` em caso de falha.

### `int cell_echo(char **args)`

*   **Propósito**: Implementa o comando `echo`, que imprime os argumentos fornecidos na saída padrão. Suporta a opção `-n` para suprimir a nova linha final.
*   **Argumentos**: `char **args` - um array de strings contendo os argumentos para o comando `echo`.
*   **Funcionalidade**: A função verifica se o segundo argumento (`args[1]`) é `"-n"`. Se for, a flag `newline` é definida como `false` e o índice de início para a impressão dos argumentos é ajustado para `2` (pulando `echo` e `-n`). Caso contrário, a impressão começa do índice `1`. A função então itera sobre os argumentos restantes, imprimindo cada um. Um espaço é adicionado entre os argumentos. Finalmente, se a flag `newline` for `true`, uma nova linha é impressa.
*   **Comportamento em Erro**: Se `args` for nulo ou `args[0]` for nulo, a função retorna `1`, indicando um erro.
*   **Retorno**: Retorna `0` em caso de sucesso e `1` em caso de falha.

Este arquivo centraliza a lógica para comandos que são parte integrante do shell, garantindo que eles sejam executados de forma eficiente e com o comportamento esperado.




## `index.c` - Lógica Principal do Shell (REPL)

O arquivo `index.c` contém a lógica central do shell, implementando o ciclo REPL (Read-Evaluate-Print/Execute-Loop). Este ciclo é o coração de qualquer shell interativo, onde o programa lê a entrada do usuário, a processa, executa o comando correspondente e repete o processo. Além do REPL, `index.c` gerencia a execução de comandos built-in e externos, bem como a divisão da linha de comando em argumentos.

### Variáveis Globais

*   `int status = 0;`:
    *   **Propósito**: Esta variável global armazena o status de saída do último comando executado. É um padrão comum em shells para que o status de saída possa ser consultado por comandos subsequentes ou scripts.

### Funções de Execução de Comandos

*   `void index_launch(char **args)`:
    *   **Propósito**: Esta função é responsável por lançar a execução de comandos externos (não built-in).
    *   **Funcionalidade**: Ela utiliza o wrapper `Fork()` para criar um novo processo filho. Se for o processo filho (`INDEX_jr` é 0, conforme definido em `index.h`), ele chama `Execvp(args[0], args)` para substituir a imagem do processo filho pelo programa especificado em `args[0]` com seus respectivos argumentos. Se for o processo pai, ele chama `Wait(&status)` para aguardar a conclusão do processo filho e coletar seu status de saída, que é armazenado na variável global `status`.
    *   **Fluxo de Controle**: Esta função é crucial para a capacidade do shell de executar programas externos, como `ls`, `grep`, etc.

*   `void index_exec(char **args)`:
    *   **Propósito**: Esta é a função principal para a execução de comandos, atuando como um despachante para comandos built-in e externos.
    *   **Funcionalidade**: A função itera sobre a estrutura global `g_builtin` (definida em `index.c` e populada com os comandos built-in). Para cada entrada em `g_builtin`, ela compara o nome do comando built-in (`g_builtin[i].builtin_name`) com o primeiro argumento da linha de comando (`args[0]`) usando `strcmp`. Se uma correspondência for encontrada, a função associada ao built-in (`g_builtin[i].foo`) é chamada com os argumentos, e o valor de retorno (status de saída do built-in) é armazenado na variável global `status`. Após a execução do built-in, a função retorna.
    *   **Comandos Built-in**: A estrutura `g_builtin` é um array de `t_builtin` (definido em `index.h`), que mapeia nomes de comandos para ponteiros de função. Atualmente, inclui `env` e `exit`. A linha comentada `{.builtin_name ="echo", .foo=index_echo};` sugere que `echo` foi considerado ou pode ser adicionado no futuro.
    *   **Execução de Comandos Externos**: Se nenhum comando built-in corresponder ao `args[0]`, a função `index_launch(args)` é chamada para tentar executar o comando como um programa externo.

### Funções de Processamento de Entrada

*   `char **index_split_line(char *line)`:
    *   **Propósito**: Esta função é responsável por tokenizar a linha de entrada do usuário em argumentos individuais.
    *   **Funcionalidade**: Ela utiliza a função `strtok` para dividir a string `line` em tokens, usando os delimitadores definidos pela macro `DEL` (espaço, tabulação, nova linha, etc.). A função aloca dinamicamente memória para armazenar os ponteiros para esses tokens. Se a capacidade do buffer for excedida, `Realloc` é usado para dobrar o tamanho do buffer, garantindo que todos os tokens possam ser armazenados. O array de tokens é terminado com `NULL`, o que é um padrão comum para arrays de strings em C.
    *   **Gerenciamento de Memória**: A memória para os tokens é alocada usando `Malloc` e `Realloc`, garantindo tratamento de erros para falhas de alocação.
    *   **Retorno**: Retorna um array de strings (`char **`) onde cada string é um argumento da linha de comando.

*   `char *index_read_line(void)`:
    *   **Propósito**: Esta função lê uma linha de entrada do usuário do `stdin`.
    *   **Funcionalidade**: Ela exibe um prompt para o usuário, que inclui o diretório de trabalho atual (obtido via `Getcwd`) e um caractere de shell (`🐚`). Em seguida, usa `getline` para ler a linha completa, incluindo espaços, até que uma nova linha seja encontrada ou o final do arquivo seja atingido. `getline` aloca dinamicamente o buffer `buf` conforme necessário.
    *   **Tratamento de Erros**: Se `getline` falhar (retornar `-1`), a função libera o buffer alocado e verifica se o final do arquivo (`feof(stdin)`) foi atingido. Se sim, imprime `"[EOF]"`; caso contrário, imprime `"getline failed"`.
    *   **Retorno**: Retorna um ponteiro para a string lida ou `NULL` em caso de erro ou final de arquivo.

### Função Principal (`main`)

*   `int main()`:
    *   **Propósito**: A função `main` é o ponto de entrada do programa shell e implementa o loop REPL.
    *   **Fluxo de Execução**: 
        1.  **Banner**: Chama `printbanner()` para exibir uma mensagem de boas-vindas no início.
        2.  **Loop REPL**: Entra em um loop infinito (`while((line = index_read_line()))`) que continua enquanto `index_read_line()` retornar uma linha válida (ou seja, não `NULL`).
        3.  **Leitura (Read)**: Dentro do loop, `index_read_line()` é chamada para obter a entrada do usuário, exibindo o prompt e lendo a linha.
        4.  **Avaliação/Tokenização (Evaluate/Lexing/Parsing)**: A linha lida é então passada para `index_split_line(line)` para ser tokenizada em argumentos.
        5.  **Execução (Execute)**: Os argumentos tokenizados são passados para `index_exec(args)`, que decide se o comando é um built-in ou um programa externo e o executa.
        6.  **Liberação de Memória (Free)**: Após a execução do comando, a memória alocada para a linha (`line`) e os argumentos (`args`) é liberada usando `free()`, prevenindo vazamentos de memória.
        7.  **Loop (Loop)**: O ciclo se repete, solicitando uma nova entrada do usuário.
    *   **Saída**: O loop termina quando `index_read_line()` retorna `NULL` (indicando EOF ou um erro fatal). O programa então retorna `EXIT_SUCCESS`.

### Estrutura `g_builtin`

```c
t_builtin g_builtin[] = {
 //   {.builtin_name ="echo", .foo=index_echo};
    {.builtin_name ="env", .foo=index_env};
    {.builtin_name ="exit", .foo=index_exit},
    {.builtin_name =NULL}

};
```

*   **Propósito**: Esta é uma variável global que armazena a lista de comandos built-in que o shell suporta. É um array de estruturas `t_builtin`, onde cada elemento associa o nome de um comando built-in a um ponteiro para a função que o implementa.
*   **Extensibilidade**: A estrutura é terminada com um elemento `NULL`, permitindo que o shell itere sobre ela para encontrar o comando built-in correto. Novas funções built-in podem ser adicionadas a este array para estender a funcionalidade do shell.

Em resumo, `index.c` orquestra o fluxo de trabalho do shell, desde a interação com o usuário até a execução de comandos, garantindo que o shell funcione como um ambiente de linha de comando interativo e responsivo.




## Conclusão

O projeto de shell em C analisado demonstra uma implementação funcional de um interpretador de linha de comando básico. A arquitetura modular, com responsabilidades bem definidas para cada arquivo (`index.h`, `utils.c`, `builtin.c`, `index.c`), contribui para a clareza e manutenibilidade do código.

Os principais recursos implementados incluem:

*   **Loop REPL**: O shell lê comandos do usuário, os avalia e os executa, repetindo o ciclo.
*   **Execução de Comandos Externos**: Capacidade de executar programas do sistema operacional através de `fork` e `execvp`.
*   **Comandos Built-in**: Implementação de comandos internos como `exit` e `env`, que são executados diretamente pelo shell para maior eficiência.
*   **Tokenização de Linha de Comando**: A entrada do usuário é dividida em tokens (comandos e argumentos) para processamento.
*   **Gerenciamento de Processos**: Utilização de `fork`, `execvp` e `wait` para criar e gerenciar processos filhos.
*   **Gerenciamento de Memória**: Uso de `malloc` e `realloc` com wrappers para tratamento de erros, garantindo alocação e realocação de memória seguras.
*   **Interface de Usuário Aprimorada**: Uso de cores ANSI para prompts e mensagens, além de um banner de boas-vindas e uma animação de desligamento.

O código demonstra boas práticas de programação em C, como o uso de wrappers para chamadas de sistema para centralizar o tratamento de erros e a liberação de memória alocada dinamicamente para evitar vazamentos.

### Possíveis Melhorias e Extensões

Embora funcional, o shell pode ser estendido com recursos adicionais para torná-lo mais robusto e completo, como:

*   **Redirecionamento de Entrada/Saída**: Implementar operadores como `>`, `<`, `>>` e `|` (pipes).
*   **Tratamento de Sinais**: Melhorar o tratamento de sinais como `SIGINT` (Ctrl+C) e `SIGTSTP` (Ctrl+Z).
*   **Variáveis de Shell**: Permitir a definição e o uso de variáveis de ambiente locais ao shell.
*   **Histórico de Comandos**: Implementar um histórico de comandos navegável.
*   **Autocompletar**: Adicionar funcionalidade de autocompletar para comandos e nomes de arquivos.
*   **Aliases**: Permitir a criação de aliases para comandos.
*   **Jobs em Background**: Suporte para executar comandos em segundo plano (usando `&`).
*   **Scripting**: Capacidade de executar scripts de shell.

Esta documentação detalhada fornece uma visão abrangente da estrutura e funcionalidade do projeto de shell em C, servindo como um guia para entender sua implementação e como base para futuras modificações ou extensões.




## Atualizações na Implementação

Desde a documentação inicial, o mini-shell passou por significativas melhorias para atender a requisitos mais complexos e oferecer uma experiência de usuário aprimorada. As principais funcionalidades adicionadas e aprimoradas incluem:

### Parsing Robusto (Tratamento de Aspas)

Uma das adições mais cruciais foi a implementação de um mecanismo de parsing mais robusto, capaz de lidar com argumentos que contêm espaços. Anteriormente, comandos como `echo Hello World` seriam interpretados como dois argumentos separados (`Hello` e `World`). Com a nova função `split_line_with_quotes`, o shell agora reconhece e processa corretamente strings delimitadas por aspas simples (`'`) ou duplas (`"`). Isso permite que o texto dentro das aspas seja tratado como um único token, mesmo que contenha caracteres de espaço. Por exemplo, `echo "Hello World from Mini-Shell"` agora imprime a frase completa como esperado. Esta funcionalidade é vital para a execução de comandos que exigem argumentos com múltiplos termos, como nomes de arquivos ou mensagens.

### Uso de `read()` e `write()`

Para um controle mais granular sobre as operações de entrada e saída, o mini-shell foi refatorado para utilizar diretamente as chamadas de sistema `read()` e `write()`. A função `read_line_from_fd` em `utils.c` foi implementada para ler a entrada caractere por caractere de um descritor de arquivo (`fd`), oferecendo maior flexibilidade na leitura de linhas. Da mesma forma, a saída do prompt do shell agora é gerenciada pela função `write()` em `index_read_line`, proporcionando uma interação mais direta e eficiente com o terminal. Essa abordagem de baixo nível garante que o shell tenha controle total sobre o fluxo de dados, otimizando o desempenho e a confiabilidade.

### Tratamento de Erro "Comando Não Encontrado"

O mini-shell agora oferece um tratamento de erro mais informativo para comandos externos que não são encontrados no `PATH` do sistema. Quando um usuário tenta executar um comando inexistente, o shell exibe uma mensagem clara: "Command not found". Essa funcionalidade é implementada na função `Execvp` em `utils.c`. Ela verifica o valor de retorno da chamada de sistema `execvp` e, em caso de falha, imprime a mensagem de erro apropriada no `stderr` antes de retornar um status de erro. Isso melhora significativamente a experiência do usuário, fornecendo feedback imediato e compreensível sobre comandos inválidos, evitando que o shell simplesmente trave ou exiba mensagens de erro genéricas do sistema.

### Redirecionamento de Entrada/Saída

Uma funcionalidade essencial para qualquer shell moderno, o redirecionamento de entrada e saída foi totalmente implementado. O mini-shell agora suporta:

*   **Redirecionamento de Saída (`>`):** Sobrescreve o conteúdo de um arquivo com a saída do comando. Exemplo: `echo "Hello World" > output.txt`.
*   **Redirecionamento de Saída para Anexar (`>>`):** Anexa a saída do comando ao final de um arquivo existente. Exemplo: `echo "Appended Line" >> output.txt`.
*   **Redirecionamento de Entrada (`<`):** Utiliza o conteúdo de um arquivo como entrada para um comando. Exemplo: `cat < input.txt`.

A função `handle_redirection` em `index.c` é responsável por identificar esses operadores na linha de comando, abrir os arquivos correspondentes e duplicar os descritores de arquivo (`dup2`) para redirecionar `stdin` ou `stdout` conforme necessário. É crucial notar que, após a execução do comando, os descritores de arquivo originais são restaurados para garantir o comportamento normal do shell para comandos subsequentes. Isso é feito salvando os descritores originais antes do redirecionamento e restaurando-os depois.

### Pipes (`|`)

O mini-shell agora permite a comunicação eficiente entre comandos através do uso de pipes. Essa funcionalidade permite que a saída de um comando seja diretamente utilizada como entrada para outro, criando cadeias de comandos poderosas. A função `execute_pipeline` em `index.c` gerencia a complexidade da criação de pipes (`pipe()`), a duplicação de descritores de arquivo e a execução de processos filhos para cada comando na pipeline. Isso garante que o fluxo de dados entre os comandos seja correto e que os processos sejam executados na ordem apropriada. Um exemplo prático é `ls -l | grep .c`, que lista todos os arquivos no diretório atual e filtra apenas aqueles que terminam com a extensão `.c`.

### Built-in `cd`

O comando `cd` (change directory) foi implementado como um comando built-in do shell. Isso significa que a mudança de diretório é tratada diretamente pelo próprio shell, sem a necessidade de invocar um processo externo. A função `index_cd` em `builtin.c` utiliza a chamada de sistema `chdir()` para alterar o diretório de trabalho atual do shell. Se nenhum argumento for fornecido, o `cd` muda para o diretório `HOME` do usuário, proporcionando uma conveniência similar aos shells de sistema. Em caso de erro, como a tentativa de mudar para um diretório inexistente, uma mensagem de erro apropriada é exibida ao usuário, como `cd error: No such file or directory`.


