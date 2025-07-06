# Funções Utilitárias e Wrappers de Chamadas de Sistema
## `utils.c` 

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



