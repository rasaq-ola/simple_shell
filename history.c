#include "shell.h"

#define HISTORY_SIZE 100

static char *history[HISTORY_SIZE];
static int history_count;

/**
 * add_history - Adds a command to the history.
 * @line: The command to add.
 */
void add_history(char *line)
{
	if (history_count == HISTORY_SIZE)
	{
		free(history[0]);
		for (int i = 1; i < HISTORY_SIZE; i++)
		{
			history[i - 1] = history[i];
		}
		history_count--;
	}
	history[history_count++] = strdup(line);
}

/**
 * print_history - Prints the command history.
 */
void print_history(void)
{
	for (int i = 0; i < history_count; i++)
	{
		printf("%d %s\n", i + 1, history[i]);
	}
}

/**
 * get_history - Retrieves a command from the history.
 * @index: The index of the command to retrieve.
 * Return: The command string or NULL if index is out of bounds.
 */
char *get_history(int index)
{
	if (index < 1 || index > history_count)
	{
		return (NULL);
	}
	return (strdup(history[index - 1]));
}
