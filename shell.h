#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

char *read_line(FILE *input);
int execute(char *line);
char **split_line(char *line);
char *get_cmd_path(char *cmd);
void print_env(void);
char *remove_comments(char *line);

void builtin_env(void);
void builtin_setenv(char **argv);
void builtin_unsetenv(char **argv);
void builtin_cd(char **argv);
int execute_builtin(char **argv);

void add_history(char *line);
void print_history(void);
char *get_history(int index);

void add_alias(char *name, char *value);
char *get_alias(char *name);
void print_aliases(void);

#endif /* SHELL_H */
