#include "index.h"
#include <unistd.h>

int index_sair(char **args) {
    (void)args;
    carregamentoAnimado();
    exit(EXIT_SUCCESS);
}

int index_ambiente(char **args) {
    extern char **environ;
    (void)args;
    if (!environ)
        return(1);
    for (int i = 0; environ[i]; i++)
        imprimir("%s\n", environ[i]);
    return(0);   
}

int index_eco(char **args) {
    int inicio = 1;
    bool novaLinha = true;

    if (!args || !args[0])
        return (1);

    // Verifica a opção -n
    if (args[1] && !strcmp(args[1], "-n")) {
        novaLinha = false;
        inicio = 2;
    }

    // Imprime cada argumento separado por espaço
    for (int i = inicio; args[i]; i++) {
        imprimir("%s", args[i]);
        if (args[i + 1])
            imprimir(" ");
    }

    // Imprime nova linha se a opção -n não estiver presente
    if (novaLinha)
        imprimir("\n");
    return (0);
}

char *ler_linha(int fd) {
    char *buffer = NULL;
    size_t tamanho_buffer = 0;
    size_t posicao = 0;
    char caractere;

    while (1) {
        ssize_t bytes_lidos = read(fd, &caractere, 1);
        
        if (bytes_lidos == -1) {
            perror(VERMELHO"erro na leitura"RST);
            free(buffer);
            return NULL;
        } else if (bytes_lidos == 0 || caractere == '\n') {
            if (buffer == NULL && bytes_lidos == 0) {
                return NULL; // Fim do arquivo
            }
            // Adiciona terminador nulo
            char *novo_buffer = Realocar(buffer, posicao + 1);
            novo_buffer[posicao] = '\0';
            return novo_buffer;
        } else {
            // Realoca o buffer se necessário
            if (posicao >= tamanho_buffer) {
                tamanho_buffer += BUFSIZ;
                char *novo_buffer = Realocar(buffer, tamanho_buffer);
                buffer = novo_buffer;
            }
            buffer[posicao++] = caractere;
        }
    }
}