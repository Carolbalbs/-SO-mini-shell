# Documentação Detalhada do Projeto Shell em C

## Introdução

Este documento fornece uma análise detalhada dos arquivos de código-fonte C que compõem um projeto de shell básico. O projeto é dividido em módulos, cada um com responsabilidades específicas:

*   `index.h`: Arquivo de cabeçalho que contém definições globais, macros e protótipos de funções.
*   `utils.c`: Implementa funções utilitárias e wrappers para chamadas de sistema.
*   `builtin.c`: Contém a implementação de comandos built-in do shell.
*   `index.c`: A lógica principal do shell, incluindo o loop de leitura, avaliação e execução de comandos (REPL).

O objetivo desta documentação é descrever a funcionalidade de cada arquivo, as funções que eles contêm e como interagem para formar o shell completo.





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


