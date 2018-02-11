#include "csapp.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAXARGS 128
//#define MAXLINE 8192
/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
extern char **environ;

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
pid_t Fork(void)
{ 
    pid_t pid;

    if ((pid = Fork()) < 0)
        unix_error("Fork error");
    return pid;
}
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv)
{
    char *delim;/* Points to first space delimiter */
    int argc; /* Number of args */
    int bg; /* Background job? */

    buf[strlen(buf)-1] = ' '; /* Replace trailing '\n' with space */
    while(*buf && (*buf == ' ')) /* Ignore leading spaces */
    {
        buf++;
    }
    /* Build argv list */
     argc =0;
    while((delim = strchr(buf, ' ')))
    {
        argv[argc++] = buf;
        *delim ='\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /*ignore spaces */
        {
            buf++;
        }
    }
    argv[argc] = NULL;

    if (argc == 0) /* ignore blank line */
        return 1;

    /*Should the job run in the background*/
    if ((bg =(*argv[argc-1] == '&')) !=0)
        argv[--argc] = NULL;

    return bg;


}

/* eval - Evaluate a command line */
void eval (char *cmdline)
{
        char *argv[MAXARGS];    /* Argument list execve() */
        char buf[MAXLINE];      /* Holds modified command line */
        int bg;                 /* Should the job run in bg or fg? */
        pid_t pid;              /* Process id */

        strcpy(buf, cmdline);
        bg = parseline(buf, argv);
        if (argv[0] == NULL)
            return;     /* Ignore empty lines */
        
        if (!builtin_command(argv)) {
            if ((pid = fork()) == 0) {  /*Child runs user job  */
                if (execve(argv[0], argv, environ) < 0) {
                    printf("%s: Command not found.\n", argv[0]);
                    exit(0);
                }
            } 

            /* Parent waits for foreground job to terminate */
            if (!bg) {
                int status;
                if (waitpid(pid, &status, 0) < 0)
                    unix_error("waitfg: waitpid error");
            }
            else
                printf("%d %s", pid, cmdline);           
        }
        return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) 
{
    if (!strcmp(argv[0], "quit")) /* quit command */
	exit(0);  

    if (!strcmp(argv[0], "SIGHUP")) /* TERMINATE | Terminal line hangup */
    printf("%s", "Command entered = SIGHUP\n");

    if (!strcmp(argv[0], "SIGINT")) /* TERMINATE | Interrupt from keyboard */
    printf("%s", "Command entered = SIGINT\n");

    if (!strcmp(argv[0], "SIGQUIT")) /* TERMINATE | Quit from keyboard */
    printf("%s", "Command entered = SIGQUIT\n");

    if (!strcmp(argv[0], "SIGILL")) /* TERMINATE | Illegal Instruction */
    printf("%s", "Command entered = SIGILL\n");
    
    if (!strcmp(argv[0], "SIGTRAP")) /* TERMINATE & DUMP CORE| Trace trap */
    printf("%s", "Command entered = SIGTRAP\n");

    if (!strcmp(argv[0], "SIGABRT")) /* TERMINATE & DUMP CORE| Abort signal from abort function */
    printf("%s", "Command entered = SIGABRT\n");

    if (!strcmp(argv[0], "SIGBUS")) /* TERMINATE | Bus error */
    printf("%s", "Command entered = SIGBUS\n");

    if (!strcmp(argv[0], "SIGFPE")) /* TERMINATE & DUMP CORE| Floating-point exception */
    printf("%s", "Command entered = SIGFPE\n");

    if (!strcmp(argv[0], "SIGKILL")) /* TERMINATE | Kill program */
    printf("%s", "Command entered = SIGKILL\n");

    if (!strcmp(argv[0], "SIGUSR1")) /* TERMINATE | User-defined signal 1 */
    printf("%s", "Command entered = SIGUSR1\n");

    if (!strcmp(argv[0], "SIGSEGV")) /* TERMINATE & DUMP CORE| Invalid memory reference (seg fault) */
    printf("%s", "Command entered = SIGSEGV\n");

    if (!strcmp(argv[0], "SIGUSR2")) /* TERMINATE | User-defined signal 1 */
    printf("%s", "Command entered = SIGUSR2\n");

    if (!strcmp(argv[0], "SIGPIPE")) /* TERMINATE | Wrote to a pipe with no reader */
    printf("%s", "Command entered = SIGPIPE\n");

    if (!strcmp(argv[0], "SIGALRM")) /* TERMINATE | Timer signal from alarm function */
    printf("%s", "Command entered = SIGALRM\n");

    if (!strcmp(argv[0], "SIGTERM")) /* TERMINATE | Software termination signal */
    printf("%s", "Command entered = SIGTERM\n");

    if (!strcmp(argv[0], "SIGSTKFLT")) /* TERMINATE | Stack fault on coprocessor */
    printf("%s", "Command entered = SIGSTKFLT\n");

    if (!strcmp(argv[0], "SIGCHLD")) /* IGNORE | A child process has stopped or terminated */
    printf("%s", "Command entered = SIGCONT\n");

    if (!strcmp(argv[0], "SIGCONT")) /* IGNORE | Continue process if stopped  */
    printf("%s", "Command entered = SIGCONT\n");

    if (!strcmp(argv[0], "SIGSTOP")) /* STOP UNTIL NEXT SIGCONT | Stop signal not from terminal */
    printf("%s", "Command entered = SIGSTOP\n");

    if (!strcmp(argv[0], "SIGTSTP")) /* STOP UNTIL NEXT SIGCONT | Stop signal from terminal */
    printf("%s", "Command entered = SIGTTIN\n");

    if (!strcmp(argv[0], "SIGTTIN")) /* STOP UNTIL NEXT SIGCONT | Background process read from terminal */
    printf("%s", "Command entered = SIGTTIN\n");

    if (!strcmp(argv[0], "SIGTTOU")) /* STOP UNTIL NEXT SIGCONT | Background process wrote to terminal */
    printf("%s", "Command entered = SIGTTOU\n");

    if (!strcmp(argv[0], "SIGURG")) /* IGNORE | Urgent condition on socket */
    printf("%s", "Command entered = SIGURG\n");
    
    if (!strcmp(argv[0], "SIGXCPU")) /* TERMINATE | CPU time limit exceeded */
    printf("%s", "Command entered = SIGXCPU\n");

    if (!strcmp(argv[0], "SIGXFSZ")) /* TERMINATE | File size limit exceeded */
    printf("%s", "Command entered = SIGXFSZ\n");

    if (!strcmp(argv[0], "SIGVTALRM")) /* TERMINATE | Virtual timer expired */
    printf("%s", "Command entered = SIGVTALRM\n");

    if (!strcmp(argv[0], "SIGPROF")) /* TERMINATE | Profiling timer expired */
    printf("%s", "Command entered = SIGPROF\n");

    if (!strcmp(argv[0], "SIGWINCH")) /* IGNORE | Window size changed */
    printf("%s", "Command entered = SIGWINCH\n");

    if (!strcmp(argv[0], "SIGIO")) /* TERMINATE | I/O now possible on a descriptor */
    printf("%s", "Command entered = SIGIO\n");

    if (!strcmp(argv[0], "SIGPWR")) /* TERMINATE | Power failure */
    printf("%s", "Command entered = SIGPWR\n");
    
    if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
    
	return 1;
    return 0;                     /* Not a builtin command */
}

int main()
{
        char cmdline[MAXLINE]; /* Command line */

        while (1) {
            /* Read */
            printf ("lsh> ");
            fgets(cmdline, MAXLINE, stdin);
            if (feof(stdin))
                exit(0);

            /* Evaluate */
            eval(cmdline);
        }
}