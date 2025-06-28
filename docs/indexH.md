# Lógica Principal do Shell (REPL)

## `index.c`

O arquivo `index.c` contém a lógica central do shell, implementando o ciclo REPL (Read-Evaluate-Print/Execute-Loop). Este ciclo é o coração de qualquer shell interativo, onde o programa lê a entrada do usuário, a processa, executa o comando correspondente e repete o processo. Além do REPL, `index.c` gerencia a execução de comandos built-in e externos, bem como a divisão da linha de comando em argumentos.

### Variáveis Globais

*   `int status = 0;`:
    *   **Propósito**: Esta variável global armazena o status de saída do último comando executado. É um padrão comum em shells para que o status de saída possa ser consultado por comandos subsequentes ou scripts.
