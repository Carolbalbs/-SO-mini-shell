#ifndef INDEX_H
#define INDEX_H
#define EX_OK 0
#define EX_OSERR 71
#define EX_UNAVAILABLE 69

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

/*
** Códigos de cores ANSI para formatação de saída no terminal:
** AMARELO    - Amarelo
** VERDE      - Verde
** CIANO      - Ciano
** VERMELHO   - Vermelho
** RST        - Resetar para cor padrão
*/
#define AMARELO    "\033[1;33m"
#define VERDE      "\033[1;32m"
#define CIANO      "\033[1;36m"
#define VERMELHO   "\033[1;31m"
#define RST        "\033[0m"

#define imprimir(...) printf(__VA_ARGS__)
#define DELIMITADORES "\n\t \v\f\r"
#define INDEX_FILHO 0

typedef struct s_comando_integrado
{
    const char     *nome_comando;
    int (*funcao)(char **);
}   t_comando_integrado;

int index_eco(char **args);   /* Implementação do comando echo */
int index_ambiente(char **args); /* Exibição de variáveis de ambiente */
int index_sair(char **args);  /* Comando de saída do shell */
char *ler_linha(int fd);

void    imprimir_banner(void);
void    carregamentoAnimado();

void    MudarDiretorio(const char *caminho);
pid_t   CriarProcesso(void);
void    ExecutarComando(const char *arquivo, char *const argv[]);
pid_t   EsperarProcesso(int *status);
pid_t   EsperarProcessoEspecifico(pid_t pid, int *status, int opcoes);
int     index_sair(char **);
void    ObterDiretorioAtual(char *, size_t);
void    *AlocarMemoria(size_t);
void    *Realocar(void *ptr, size_t tamanho);

#endif

