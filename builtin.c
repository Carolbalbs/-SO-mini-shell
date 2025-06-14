#include "index.h"

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
int	cell_echo(char **args)
{
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