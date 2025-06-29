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

#
(Content truncated due to size limit. Use line ranges to read in chunks)


## Comparação de Requisitos: Projeto Mini-Shell vs. Documento `Projeto.pdf`

Esta seção avalia o projeto mini-shell fornecido em relação aos requisitos e funcionalidades descritas no documento `Projeto.pdf`. O objetivo é identificar quais aspectos foram implementados e quais ainda não foram.

### Requisitos Implementados

O projeto mini-shell demonstra a implementação bem-sucedida de várias funcionalidades essenciais, conforme especificado no `Projeto.pdf`:

*   **Prompt Interativo**: O shell exibe um prompt (`🐚<diretório_atual>🐚$>`) que indica que está pronto para receber comandos, cumprindo o requisito de um prompt interativo.
*   **Leitura de Comandos com Argumentos**: A função `index_read_line` lê a linha completa digitada pelo usuário, e `index_split_line` a tokeniza em comandos e argumentos, permitindo a entrada de comandos como `ls -l` ou `echo Ola mundo`.
*   **Criação de Processos (`fork()`):** A função `Fork()` em `utils.c` encapsula a chamada de sistema `fork()`, criando um novo processo filho para a execução de comandos externos.
*   **Execução de Comandos (`execvp()`):** A função `Execvp()` em `utils.c` é um wrapper para `execvp()`, utilizada pelo processo filho para substituir sua imagem pelo comando digitado.
*   **Espera pela Execução (`wait()`):** A função `Wait()` em `utils.c` encapsula a chamada de sistema `wait()`, garantindo que o processo pai aguarde a conclusão do processo filho antes de continuar.
*   **Encerramento com `exit`**: O comando built-in `exit` (implementado como `index_exit` em `builtin.c`) permite que o usuário finalize o shell de forma controlada, incluindo uma animação de desligamento.
*   **Modularização Mínima**: O projeto é bem modularizado, com funções separadas para:
    *   Leitura (`index_read_line`)
    *   Parsing/Tokenização (`index_split_line`)
    *   Execução (`index_exec`, `index_launch`)
    *   Controle do loop principal (`main`)
*   **Tratamento de Erros com Mensagens Amigáveis**: As funções wrapper em `utils.c` utilizam `perror` para exibir mensagens de erro amigáveis em caso de falha de chamadas de sistema. A função `index_exec` tenta executar comandos externos se não forem built-ins, e `index_read_line` lida com erros de `getline`.
*   **Uso de `fork()`, `execvp()`, `wait()`:** Todas essas chamadas de sistema são utilizadas através de funções wrapper no arquivo `utils.c`.
*   **Execução de `echo` com argumentos**: O comando `echo` é implementado como um built-in (`cell_echo`) e suporta argumentos, incluindo a opção `-n`.

### Requisitos Não Implementados ou Parcialmente Atendidos

Alguns requisitos do `Projeto.pdf` não foram totalmente implementados ou não há evidência clara de sua implementação no código fornecido:

*   **Uso de `read()` para Entrada Padrão**: O documento especifica o uso de `read()` para tratar a entrada padrão. No entanto, o projeto utiliza `getline()`, que é uma função de nível mais alto para leitura de linhas. Embora `getline()` seja eficiente, não atende diretamente ao requisito de usar `read()`.
*   **Uso de `write()` para Saída de Dados**: O documento exige o uso de `write()` para saída de dados. O projeto utiliza `printf` (através da macro `p`), que é uma função de nível mais alto e não `write()` diretamente.
*   **Execução de `ls` e `cat` com Argumentos**: Embora o mecanismo para executar comandos externos (`index_launch`) esteja presente e deva ser capaz de executar `ls` e `cat` com argumentos (assumindo que estejam no `PATH` do sistema), o projeto não inclui testes explícitos ou demonstrações no código ou na documentação gerada que confirmem a execução *correta e com argumentos* desses comandos específicos. O requisito pede para 


executar *no mínimo três comandos diferentes corretamente e com argumentos (ls, cat, echo)*. O `echo` está implementado como built-in, mas `ls` e `cat` não são built-ins e não há garantia explícita de seu funcionamento no código.
*   **Tratar Erros com Mensagens Amigáveis (comando não encontrado)**: Embora haja tratamento de erros para falhas de chamadas de sistema, não há uma mensagem explícita de "comando não encontrado" quando um comando digitado pelo usuário não é um built-in e não pode ser executado via `execvp` (por exemplo, se o comando não existe no `PATH`). O `Execvp` apenas imprime "Failed" e sai.
*   **Redirecionamento e Pipes (`dup2()`, `pipe()`):** O documento menciona `dup2()` e `pipe()` como funcionalidades avançadas para redirecionamento e pipes. O projeto mini-shell não implementa nenhuma dessas funcionalidades.
*   **Arquivo README**: O `Projeto.pdf` exige a entrega de um arquivo README detalhado com informações sobre compilação, chamadas de sistema usadas, exemplos, e limitações. Embora eu tenha gerado uma documentação detalhada, um arquivo README específico com esses pontos não foi criado como parte do projeto mini-shell.
*   **Vídeo Curto Demonstrando o Uso do Shell**: O requisito de entrega inclui um vídeo de demonstração, o que não é uma funcionalidade do código em si, mas um requisito de apresentação do projeto.

### Resumo das Funcionalidades Não Implementadas

Com base na análise, as seguintes funcionalidades e requisitos do `Projeto.pdf` não foram implementados no projeto mini-shell fornecido:

1.  **Uso direto de `read()` para entrada padrão.**
2.  **Uso direto de `write()` para saída de dados.**
3.  **Tratamento explícito de "comando não encontrado" com mensagem amigável.**
4.  **Redirecionamento de entrada/saída (`<`, `>`, `>>`).**
5.  **Pipes (`|`).**
6.  **Geração de um arquivo README conforme as especificações.**
7.  **Criação de um vídeo de demonstração.**

É importante notar que a ausência de `ls` e `cat` como built-ins não significa que o shell não possa executá-los, mas sim que o requisito de *executar no mínimo três comandos diferentes corretamente e com argumentos (ls, cat, echo)* não foi explicitamente demonstrado para `ls` e `cat` no código ou na documentação gerada, apenas para `echo`.


