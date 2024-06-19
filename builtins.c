#include "shell.h"

/**
 * builtin_env - Prints the environment variables.
 */
void builtin_env(void)
{
	extern char **environ;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * builtin_setenv - Sets or modifies an environment variable.
 * @argv: Array of arguments.
 */
void builtin_setenv(char **argv)
{
	if (argv[1] && argv[2])
	{
		if (setenv(argv[1], argv[2], 1) != 0)
		{
			perror("setenv");
		}
	}
	else
	{
		write(STDOUT_FILENO, "Usage: setenv VAR VALUE\n", 24);
	}
}

/**
 * builtin_unsetenv - Unsets an environment variable.
 * @argv: Array of arguments.
 */
void builtin_unsetenv(char **argv)
{
	if (argv[1])
	{
		if (unsetenv(argv[1]) != 0)
		{
			perror("unsetenv");
		}
	}
	else
	{
		write(STDOUT_FILENO, "Usage: unsetenv VAR\n", 20);
	}
}

/**
 * builtin_cd - Changes the current directory.
 * @argv: Array of arguments.
 */
void builtin_cd(char **argv)
{
	if (argv[1] == NULL)
	{
		argv[1] = getenv("HOME");
	}
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
	}
}

/**
 * execute_builtin - Executes built-in commands.
 * @argv: Array of arguments.
 * Return: 1 if the command is a built-in, 0 for "exit", or -1 otherwise.
 */
int execute_builtin(char **argv)
{
	if (strcmp(argv[0], "env") == 0)
	{
		builtin_env();
		return (1);
	}

	if (strcmp(argv[0], "setenv") == 0)
	{
		builtin_setenv(argv);
		return (1);
	}

	if (strcmp(argv[0], "unsetenv") == 0)
	{
		builtin_unsetenv(argv);
		return (1);
	}

	if (strcmp(argv[0], "cd") == 0)
	{
		builtin_cd(argv);
		return (1);
	}

	if (strcmp(argv[0], "exit") == 0)
	{
		return (0);
	}

	return (-1);
}
