#ifndef INDEX_H
#define INDEX_H
#define EX_OK
#define EX_OSERR 71
#define EX_UNAVAILABLE 69

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>

/*
** ANSI Color codes for terminal output formatting:
** Y    - Yellow
** G    - Green
** C    - Cyan
** RED  - Red
** RST  - Reset to default color
*/
#define Y		"\033[1;33m"
#define G		"\033[1;32m"
#define C 		"\033[1;36m"
#define RED		"\033[1;31m"
#define RST 	"\033[0m"

#define p(...) printf(__VA_ARGS__)
#define DEL "\n\t \v\f\r"
#define INDEX_jr 0

typedef struct s_builtin
{
    const char     *builtin_name;
    int (*foo)(char **);
}   t_builtin;

int	index_echo(char **args);  /* Echo command implementation */
int	index_env(char **args);   /* Environment variables display */
int	index_exit(char **args);  /* Shell exit command */

void    printbanner(void);
void    spinnerLoading();

void    Chdir(const char *path);
pid_t   Fork(void);
void    Execvp(const char *file,char *const argv[]);
pid_t   Wait(int *status);
pid_t   Waitpid(pid_t pid, int *status, int options);
int     index_exit(char **);
void    Getcwd(char *, size_t);
void    *Malloc(size_t);
void	*Realloc(void *ptr, size_t size);

#endif