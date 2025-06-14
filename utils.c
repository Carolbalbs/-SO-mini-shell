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
        perror(RED"Realloc"RST);
        exit(EXIT_FAILURE);
    }
    return(new_ptr);
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
        "[            ]",
        "[=           ]",
        "[==          ]",
        "[===         ]",
        "[====        ]",
        "[=====       ]",
        "[======      ]",
        "[=======     ]",
        "[========    ]",
        "[=========   ]",
        "[==========  ]",
        "[=========== ]",
        "[===========💥]",
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