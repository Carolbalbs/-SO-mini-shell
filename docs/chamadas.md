# Conceitos Chamadas ao Sistema Utilizadas


## O mini-shell faz uso extensivo das seguintes chamadas de sistema POSIX para sua operação:

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
