#include "index.h"

#include "index.h"

int    status = 0;


t_builtin g_builtin[] = {
    {.builtin_name ="echo", .foo=index_echo},
    {.builtin_name ="env", .foo=index_env},
    {.builtin_name ="exit", .foo=index_exit},
    {.builtin_name =NULL}
    
};
void index_launch(char **args){

    if (Fork() == INDEX_jr)
         Execvp(args[0],args);
    else     
        Wait(&status);
        // Waitpid(index_jr, &status, 0);
    

}  
 /* */  
void index_exec(char **args){
    int     i;
    const char *curr;
    
    i = 0;
    while ((curr = g_builtin[i].builtin_name)){
    
        if (!strcmp(curr, args[0])){
            status = g_builtin[i].foo(args);
            return ;
        }
        ++i;
    }
    index_launch(args);
}

char **index_split_line(char *line){
    char            **tokens;
    unsigned int    position;
    size_t          bufsize; 

    bufsize = BUFSIZ;
    tokens = Malloc(bufsize*sizeof *tokens);
    position = 0;

    for(char *token = strtok(line, DEL); token; token = strtok(NULL, DEL)){
        tokens[position++] = token;
        if (position >= bufsize){
            
            bufsize *= 2;
            tokens = Realloc(tokens, bufsize * sizeof(*tokens));
        }
    }
    tokens[position] = NULL;
    return tokens;
}
char *index_read_line(void) {
    char cwd[BUFSIZ];
    Getcwd(cwd, sizeof(cwd));
    p(C"🐚%s🐚"RST"$>", cwd);
    fflush(stdout);  // Garante que o prompt seja exibido antes da leitura

    char *line = read_line(STDIN_FILENO);
    
    if (line == NULL) {
        if (errno) {
            p(RED"read failed"RST);
        } else {
            p(RED"[EOF]"RST);
        }
    }
    
    return line;
}

int main(){
    
    char *line;
    char **args;
    printbanner();
    //REPL
    //READ -> EVALUATE -> PRINT/EXECUTE -> LOOP
    
    //1)prompt + get line
    while((line = index_read_line())){
        
        //2) get tokens gettok
                    // ->lexing ->parsing EVALUATING
        args = index_split_line(line);
        
        //3) Exec
        index_exec(args);
        //4) free
        free(line);
        free(args);


    }
    
    return EXIT_SUCCESS;
}