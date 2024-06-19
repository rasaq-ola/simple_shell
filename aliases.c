#include "shell.h"

/**
 * struct alias - Represents an alias with a name and value.
 * @name: The name of the alias.
 * @value: The value of the alias.
 */
struct alias
{
	char *name;
	char *value;
};

#define ALIAS_SIZE 50

static struct alias aliases[ALIAS_SIZE];
static int alias_count;

/**
 * add_alias - Adds an alias to the alias list.
 * @name: The name of the alias.
 * @value: The value of the alias.
 */
void add_alias(char *name, char *value)
{
	if (alias_count == ALIAS_SIZE)
	{
		fprintf(stderr, "alias: alias table full\n");
		return;
	}
	aliases[alias_count].name = strdup(name);
	aliases[alias_count].value = strdup(value);
	alias_count++;
}

/**
 * get_alias - Retrieves the value of an alias by its name.
 * @name: The name of the alias.
 *
 * Return: The value of the alias if found, otherwise NULL.
 */
char *get_alias(char *name)
{
	int i;

	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			return (strdup(aliases[i].value));
		}
	}
	return (NULL);
}

/**
 * print_aliases - Prints all stored aliases.
 */
void print_aliases(void)
{
	int i;

	for (i = 0; i < alias_count; i++)
	{
		printf("%s='%s'\n", aliases[i].name, aliases[i].value);
	}
}
