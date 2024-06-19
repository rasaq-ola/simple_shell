#include "shell.h"

/**
 * main - Entry point for the shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	char *line;
	int status;
	FILE *input = stdin;

	if (argc > 1)
	{
		input = fopen(argv[1], "r");
		if (input == NULL)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}
	}

	do
	{
		if (isatty(STDIN_FILENO) && input == stdin)
		{
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		}
		line = read_line(input);
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO) && input == stdin)
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			if (input != stdin)
			{
				fclose(input);
			}
			exit(0);
		}
		status = execute(line);
		free(line);
	} while (status);

	return (0);
}
