# Implementação de Comandos Built-in

## `builtin.c` 

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



