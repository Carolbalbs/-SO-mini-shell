#include "index.h"



//WRAPPERS

void ObterDiretorioAtual(char *buf, size_t tamanho) {
    if (NULL == getcwd(buf, tamanho))
        perror(VERMELHO"erro em getcwd"RST); 
}

void *AlocarMemoria(size_t tamanho) {
    void *ptr;

    if (tamanho == 0)
        return(NULL);
    ptr = malloc(tamanho);
    if (!ptr) {
        perror(VERMELHO"erro na alocação"RST);
        exit(EXIT_FAILURE);
    }
    return (ptr);
}

void *Realocar(void *ptr, size_t tamanho) {
    void *novo_ptr;

    novo_ptr = realloc(ptr, tamanho);
    if (!novo_ptr && tamanho != 0) {
        perror(VERMELHO"erro na realocação"RST);
        exit(EXIT_FAILURE);
    }
    return(novo_ptr);
}

pid_t CriarProcesso(void) {
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror(VERMELHO"erro ao criar processo"RST);
        exit(EX_OSERR);
    }
    return(pid);
}

void ExecutarComando(const char *arquivo, char *const argv[]) {
    if (!arquivo || !argv) {
        fprintf(stderr, VERMELHO"argumentos inválidos para ExecutarComando\n"RST);
        exit(EXIT_FAILURE);
    }
    if (execvp(arquivo, argv) == -1) {
        perror(VERMELHO"comando não encontrado"RST);
        exit(EX_UNAVAILABLE);
    }
}

pid_t EsperarProcesso(int *status) {
    pid_t resultado;

    if (!status) {
        fprintf(stderr, VERMELHO"EsperarProcesso: argumento status é obrigatório\n"RST);
        return (-1);
    }
    resultado = wait(status);
    if (resultado == -1)
        perror(VERMELHO"erro ao esperar processo"RST);
    if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status); 
    return (resultado);
}


void imprimir_banner(void){
imprimir(VERDE"███╗   ███╗██╗███╗   ██╗██╗    ███████╗██╗  ██╗███████╗██╗     ██╗\n"     
"████╗ ████║██║████╗  ██║██║    ██╔════╝██║  ██║██╔════╝██║     ██║\n"     
"██╔████╔██║██║██╔██╗ ██║██║    ███████╗███████║█████╗  ██║     ██║\n"     
"██║╚██╔╝██║██║██║╚██╗██║██║    ╚════██║██╔══██║██╔══╝  ██║     ██║\n"     
"██║ ╚═╝ ██║██║██║ ╚████║██║    ███████║██║  ██║███████╗███████╗███████╗\n"
"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
"                                                                       \n"RST);
}
void carregamentoAnimado() 
{
    const char *carregando[] = {
        "[      ]",
        "[=     ]",
        "[==    ]",
        "[===   ]",
        "[====💥]",
    };
 const int quadros = sizeof(carregando) / sizeof(carregando[0]);

	imprimir(VERMELHO"Saindo do shell...\n"RST);

    // Loop through the "charging" animation for 3 seconds
    for (int i = 0; i < quadros; i++) {
        imprimir("\r" AMARELO "%s" RST, carregando[i]);
        fflush(stdout);  // Force update the console
        usleep(421337);  
    }
	imprimir(CIANO"\n✅ EXIT ✅\n"RST);
	exit(EX_OK);
}