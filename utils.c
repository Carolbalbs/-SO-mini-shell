#include "index.h"



//WRAPPERS

void Getcwd(char *buf, size_t size){
    if (NULL == getcwd(buf , size))
        perror(RED"getcwd FAILED"RST); 
}
void *Malloc(size_t size){
    void     *ptr;

    if(size == 0)
        return(NULL);
    ptr = malloc(size);
    if(!ptr){
        perror(RED"Malloc Failed"RST);
        exit(EXIT_FAILURE);
    }
   return (ptr);
}
void *Realloc(void *ptr, size_t size){
    void    *new_ptr;

    new_ptr = realloc(ptr, size);
    if (!new_ptr && size != 0){
        perror(RED"Realloc Failed"RST);
        exit(EXIT_FAILURE);
    }
    return(new_ptr);
}

pid_t Fork(void){
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror(RED"Fork Failed"RST);
        exit(EX_OSERR);
    }
    return(pid);
}

void	Execvp(const char *file, char *const argv[]){
    if (!file || !argv){
    
        fprintf(stderr, RED"Execvp invalid arguments\n"RST);
        exit(EXIT_FAILURE);
    }
    if (execvp(file, argv) == -1){
    
        perror(RED"Failed"RST);
        exit(EX_UNAVAILABLE);
    }
    
}

pid_t	Wait(int *status)
{
	pid_t	result;

	if (!status)
	{
		fprintf(stderr, RED"Wait: status argument required\n"RST);
		return (-1);
	}
	result = wait(status);
	if (result == -1)
		perror(RED"Wait failed"RST);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status); 
	return (result);
}

pid_t	Waitpid(pid_t pid, int *status, int options)
{
	pid_t	result;

	if (!status)
		return (-1);
	result = waitpid(pid, status, options);
	if (result == -1)
		perror(RED"Waitpid failed"RST);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status); 
	return (result);
}


void printbanner(void){
p(G"███╗   ███╗██╗███╗   ██╗██╗    ███████╗██╗  ██╗███████╗██╗     ██╗\n"     
"████╗ ████║██║████╗  ██║██║    ██╔════╝██║  ██║██╔════╝██║     ██║\n"     
"██╔████╔██║██║██╔██╗ ██║██║    ███████╗███████║█████╗  ██║     ██║\n"     
"██║╚██╔╝██║██║██║╚██╗██║██║    ╚════██║██╔══██║██╔══╝  ██║     ██║\n"     
"██║ ╚═╝ ██║██║██║ ╚████║██║    ███████║██║  ██║███████╗███████╗███████╗\n"
"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
"                                                                       \n"RST);
}
void spinnerLoading() 
{
    const char *charging[] = {
        "[      ]",
        "[=     ]",
        "[==    ]",
        "[===   ]",
        "[====💥]",
    };
    const int frames = sizeof(charging) / sizeof(charging[0]);

	p(RED"Shutting down...\n"RST);

    // Loop through the "charging" animation for 3 seconds
    for (int i = 0; i < frames; i++) {
        p("\r" Y "%s" RST, charging[i]);
        fflush(stdout);  // Force update the console
        usleep(421337);  
    }
	p(C"\n✅ EXIT ✅\n"RST);
	exit(X_OK);
}