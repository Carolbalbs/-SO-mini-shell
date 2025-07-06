#include "index.h"
#include <unistd.h>

int index_exit(char **args){

    (void)args;
    spinnerLoading();
    exit(EXIT_SUCCESS);
}

int index_env(char **args){

    extern char **environ;
    (void)args;
    if (!environ)
        return(1);
    for (int i = 0; environ[i]; i++)
        p("%s\n",environ[i]);
    return(0);   
}

int	index_echo(char **args){


	int start = 1;
	bool newline = true;

	if (!args || !args[0])
		return (1);

	// Check for the -n option
	if (args[1] && !strcmp(args[1], "-n"))
	{
		newline = false;
		start = 2;
	}

	// Print each argument separated by a space
	for (int i = start; args[i]; i++)
	{
		p("%s", args[i]);
		if (args[i + 1])
			p(" ");
	}

	// Print newline if -n option is not present
	if (newline)
		p("\n");
	return (0);
}


char *read_line(int fd) {
    char *buffer = NULL;
    size_t bufsize = 0;
    size_t pos = 0;
    char ch;

    while (1) {
        ssize_t bytes_read = read(fd, &ch, 1);
        
        if (bytes_read == -1) {
            perror(RED"read failed"RST);
            free(buffer);
            return NULL;
        } else if (bytes_read == 0 || ch == '\n') {
            if (buffer == NULL && bytes_read == 0) {
                return NULL; // EOF
            }
            // Adiciona terminador nulo
            char *new_buffer = Realloc(buffer, pos + 1);
            new_buffer[pos] = '\0';
            return new_buffer;
        } else {
            // Realoca o buffer se necessário
            if (pos >= bufsize) {
                bufsize += BUFSIZ;
                char *new_buffer = Realloc(buffer, bufsize);
                buffer = new_buffer;
            }
            buffer[pos++] = ch;
        }
    }
}