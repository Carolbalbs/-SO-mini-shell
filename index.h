#ifndef INDEX_H
# define INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
#define DELL "\n\t\v\f\r"

typedef struct s_builtin
{
    const char     *builtin_name;
    int (*foo)(char **);
}   t_builtin;

int    index_exit(char **);
void    spinnerLoading();
void    Getcwd(char *, size_t);
void    printbanner(void);
void    *Malloc(size_t);
void	*Realloc(void *ptr, size_t size);
#endif