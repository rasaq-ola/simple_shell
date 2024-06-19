#include "shell.h"

void builtin_env(void)
{
    extern char **environ;
    for (int i = 0; environ[i] != NULL; i++) {
        write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
    }
}

void builtin_setenv(char **argv)
{
    if (argv[1] && argv[2]) {
        if (setenv(argv[1], argv[2], 1) != 0) {
            perror("setenv");
        }
    } else {
        write(STDOUT_FILENO, "Usage: setenv VAR VALUE\n", 24);
    }
}

void builtin_unsetenv(char **argv)
{
    if (argv[1]) {
        if (unsetenv(argv[1]) != 0) {
            perror("unsetenv");
        }
    } else {
        write(STDOUT_FILENO, "Usage: unsetenv VAR\n", 20);
    }
}

void builtin_cd(char **argv)
{
    if (argv[1] == NULL) {
        argv[1] = getenv("HOME");
    }
    if (chdir(argv[1]) != 0) {
        perror("cd");
    }
}

int execute_builtin(char **argv)
{
    if (strcmp(argv[0], "env") == 0) {
        builtin_env();
        return (1);
    }

    if (strcmp(argv[0], "setenv") == 0) {
        builtin_setenv(argv);
        return (1);
    }

    if (strcmp(argv[0], "unsetenv") == 0) {
        builtin_unsetenv(argv);
        return (1);
    }

    if (strcmp(argv[0], "cd") == 0) {
        builtin_cd(argv);
        return (1);
    }

    if (strcmp(argv[0], "exit") == 0) {
        return (0);
    }

    return (-1);
}
