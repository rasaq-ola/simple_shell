#include "shell.h"

#define TOKEN_DELIM " \t\r\n\a"

/**
 * split_line - Splits a line into tokens.
 * @line: The line to split.
 * Return: An array of tokens.
 */
char **split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens)
			{
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * execute - Executes a command line.
 * @line: The command line to execute.
 * Return: 1 if the shell should continue running, 0 if it should terminate.
 */
int execute(char *line)
{
	char **argv;
	pid_t pid;
	int status;
	char *cmd_path;

	line = remove_comments(line);
	add_history(line);

	char *cmd = strtok(line, ";");
	while (cmd != NULL)
	{
		argv = split_line(cmd);

		if (argv[0] == NULL)
		{
			free(argv);
			cmd = strtok(NULL, ";");
			continue;
		}

		int builtin_status = execute_builtin(argv);
		if (builtin_status != -1)
		{
			free(argv);
			if (builtin_status == 0)
			{
				return (0);
			}
			cmd = strtok(NULL, ";");
			continue;
		}

		cmd_path = get_cmd_path(argv[0]);
		if (cmd_path == NULL)
		{
			perror("./shell");
			free(argv);
			cmd = strtok(NULL, ";");
			continue;
		}

		pid = fork();
		if (pid == 0)
		{
			if (execve(cmd_path, argv, NULL) == -1)
			{
				perror("./shell");
			}
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("fork");
		}
		else
		{
			do
			{
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}

		free(argv);
		free(cmd_path);

		cmd = strtok(NULL, ";");
	}

	return (1);
}
