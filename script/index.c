#include "index.h"

int status = 0;

t_comando_integrado comandos_integrados[] = {
    {.nome_comando ="echo", .funcao=index_eco},
    {.nome_comando ="env", .funcao=index_ambiente},
    {.nome_comando ="exit", .funcao=index_sair},
    {.nome_comando =NULL}
};

void executar_comando(char **args) {
    if (CriarProcesso() == INDEX_FILHO)
        ExecutarComando(args[0], args);
    else
        EsperarProcesso(&status);
}

void executar_comando_integrado(char **args) {
    int i;
    const char *atual;
    
    i = 0;
    while ((atual = comandos_integrados[i].nome_comando)) {
        if (!strcmp(atual, args[0])) {
            status = comandos_integrados[i].funcao(args);
            return;
        }
        ++i;
    }
    executar_comando(args);
}

char **dividir_linha(char *linha) {
    char **tokens;
    unsigned int posicao;
    size_t tamanho_buffer;

    tamanho_buffer = BUFSIZ;
    tokens = AlocarMemoria(tamanho_buffer * sizeof *tokens);
    posicao = 0;

    for (char *token = strtok(linha, DELIMITADORES); token; token = strtok(NULL, DELIMITADORES)) {
        tokens[posicao++] = token;
        if (posicao >= tamanho_buffer) {
            tamanho_buffer *= 2;
            tokens = Realocar(tokens, tamanho_buffer * sizeof(*tokens));
        }
    }
    tokens[posicao] = NULL;
    return tokens;
}

char *ler_linha_entrada(void) {
    char dir_atual[BUFSIZ];
    ObterDiretorioAtual(dir_atual, sizeof(dir_atual));
    imprimir(CIANO"🐚%s🐚"RST"$>", dir_atual);
    fflush(stdout);

    char *linha = ler_linha(STDIN_FILENO);
    
    if (linha == NULL) {
        if (errno) {
            imprimir(VERMELHO"erro na leitura"RST);
        } else {
            imprimir(VERMELHO"[FIM DO ARQUIVO]"RST);
        }
    }
    
    return linha;
}

int main() {
    char *linha;
    char **args;
    imprimir_banner();
    
    // REPL (Read-Eval-Print Loop)
    while ((linha = ler_linha_entrada())) {
        args = dividir_linha(linha);
        executar_comando_integrado(args);
        free(linha);
        free(args);
    }
    
    return EXIT_SUCCESS;
}