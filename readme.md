# 🐚 Projeto Shell em C

## 📘 Introdução

Este projeto implementa um shell básico em linguagem C, dividido em módulos, cada um com responsabilidades específicas:

- `index.h`: Arquivo de cabeçalho com definições globais, macros e protótipos.
- `utils.c`: Funções auxiliares e wrappers (empacotadores) de chamadas de sistema.
- `builtin.c`: Comandos internos do shell (`echo`, `env`, `exit`).
- `index.c`: Loop principal do shell (REPL).

---

## 🎯 Objetivo

Descrever a funcionalidade de cada arquivo, suas interações e sua contribuição para a construção de um shell funcional com:

- Comandos internos
- Execução de programas externos
- Prompt colorido
- Animação de saída
- Tratamento básico de erros

---

## 🗂️ Estrutura dos Arquivos

### `index.h` — Cabeçalho Principal

#### 🔸 Definições e Códigos de Saída

```c
#define EX_OK         0   // Execução normal
#define EX_OSERR     71   // Erro no sistema operacional
#define EX_UNAVAILABLE 69 // Recurso necessário indisponível
```

#### 🔸 Bibliotecas Importadas

```c
Inclui bibliotecas padrão e POSIX: stdio.h, stdlib.h, unistd.h, string.h, stdbool.h, sys/wait.h, errno.h.
    '<stdio.h>' Funções para entrada e saída padrão
    '<stdlib.h>' Funções para gerenciamento de memória, conversões, controle de execução, etc.
    '<unistd.h>' Funções para operações de sistema
    '<string.h>' Funções para manipulação de strings e blocos de memória.
    '<stdbool.h>' Suporte ao tipo bool
    '<sys/wait.h>' Funções e macros para esperar o término de processos filhos.
    '<errno.h>' Variável global errno e definições de códigos de erro do sistema.
```

#### 🔸 Macros Definidas

```c
#define AMARELO    "\033[1;33m"
#define VERDE      "\033[1;32m"
#define CIANO      "\033[1;36m"
#define VERMELHO   "\033[1;31m"
#define RST        "\033[0m"
#define imprimir(...) printf(__VA_ARGS__)
#define DELIMITADORES "\n\t \v\f\r"
#define INDEX_FILHO 0 (para identificar o processo filho após um 'fork()')
```

#### 🔸 Define a estrutura 't_comando_integrado' para mapear nomes de comandos internos às suas funções correspondentes.

#### 🔸 Protótipos de Funções

```c
Comandos internos (não criam processos filhos):

'index_eco' - Implementa o comando echo, que imprime os argumentos na tela.
'index_ambiente' - Implementa o comando env, que exibe todas as variáveis de ambiente do sistema.
'index_sair' - Implementa o comando exit, que finaliza o shell.

Entrada:

'ler_linha' - Lê uma linha do terminal (baixo nível com read)
'ler_linha_entrada' - Mostra o prompt + chama ler_linha()
'dividir_linha' - Divide a linha em tokens (comandos e argumentos)

Execução:

'CriarProcesso' - Cria um novo processo (via fork()) e encerra se falhar.
'ExecutarComando' - Executa o comando no processo filho (execvp()) que encerra o programa caso o comando não seja encontrado.
'EsperarProcesso' - Espera o término de um processo filho (wait()), captura e retorna o status de saída do processo filho.
'EsperarProcessoEspecifico' - Espera um filho específico (waitpid())

Utilitários:

'ObterDiretorioAtual' - Obter o caminho absoluto do diretório atual
'AlocarMemoria' - Alocar memória com malloc() com segurança
'Realocar' - Redimensionar blocos de memória com realloc() de forma segura
'imprimir_banner' - Exibir arte ASCII colorida no início do shell
'carregamentoAnimado' - Mostrar uma animação visual divertida ao encerrar o shell '(exit)'
```

### `utils.c` - Funções Auxiliares e Wrappers

#### 🔸 Gerenciamento de diretório:

```c
'ObterDiretorioAtual(char *buf, size_t tamanho)':

Usa 'getcwd()' para obter o caminho atual. Exibe erro com 'perror' se falhar.
```

#### 🔸 Gerenciamento de memória:

```c
'AlocarMemoria(size_t tamanho)':

Wrapper para 'malloc()' com verificação de erro.

'Realocar(void *ptr, size_t tamanho)':

Wrapper para 'realloc()' com verificação de erro.
```

#### 🔸 Processos:

```c
'CriarProcesso()':

Wrapper para 'fork()', encerra se falhar.

'ExecutarComando()':

Wrapper para 'execvp()' que encerra o programa caso o comando não seja encontrado.

'EsperarProcesso()':

Wrapper para 'wait()', captura e retorna o status de saída do processo filho.
```

#### 🔸 Interface:

```c
'imprimir_banner()':

Exibe uma arte em ASCII no início do shell.

'carregamentoAnimado()':

Mostra uma animação com "=", simulando carregamento antes de encerrar o shell.
```

### `builtin.c` - Comandos Internos

#### 🔸 'index_sair(char **args)'

```c
Comando interno 'exit'.

Ignora argumentos.

Chama 'carregamentoAnimado()' e encerra com 'exit(EXIT_SUCCESS)'.
```

#### 🔸 'index_ambiente(char **args)'

```c
Comando interno 'env'.

Itera sobre 'environ' e imprime cada variável de ambiente.

Retorna 1 se 'environ' for NULL.
```

#### 🔸 'index_eco(char **args)'

```c
Comando interno 'echo'.

Suporta opção '-n' para não imprimir nova linha.

Imprime argumentos separados por espaço, a partir de 'args[1]' ou 'args[2]' (se '-n' estiver presente).
```

#### 🔸 'ler_linha(int fd)'

```c
Função auxiliar para ler linha de entrada usando 'read()' caractere por caractere.

Lida com realocação dinâmica do buffer.

Retorna string terminada com '\0'.
```

### `index.c` - Lógica Principal (REPL)

#### 🔸 Variável global:

```c
'int status': guarda o código de saída do último comando.

'comandos_integrados[]'

Lista de comandos internos: 'echo', 'env', 'exit'.
```

#### 🔸 Funções principais:

```c
'executar_comando(char **args)':

Cria processo com 'CriarProcesso()' e executa comando externo.

'executar_comando_integrado(char **args)':

Verifica se o comando é interno. Se for, executa; caso contrário, chama 'executar_comando()'.

'dividir_linha(char *linha)':

Tokeniza a linha de entrada com 'strtok()' usando delimitadores definidos.

'ler_linha_entrada()':

Exibe prompt com diretório atual e chama 'ler_linha(STDIN_FILENO)' para ler entrada.
```

#### 🔸 'main()'

```c
Exibe banner.

Executa ciclo REPL:

Lê a linha

Divide em tokens

Executa o comando (interno ou externo)

Libera memória
```

### Exemplos de Compilação e Execução

#### 🔸 Compilação:

gcc -Wall -Wextra -Werror index.c utils.c builtin.c -o minishell

#### 🔸 Execução:

./minishell

#### 🔸 Exemplos de uso:

echo Olá mundo
echo -n sem quebra
env
ls -l
exit

### Resumo

#### 🔸 Este projeto implementa um shell simples em C, com suporte a:

Comandos internos: 'exit', 'echo', 'env'

Execução de comandos externos

Animações e prompt com cores

Tratamento de erros com mensagens visuais
