#include "shell.h"

#define ALIAS_SIZE 50

typedef struct alias {
    char *name;
    char *value;
} alias_t;

static alias_t aliases[ALIAS_SIZE];
static int alias_count = 0;

void add_alias(char *name, char *value)
{
    if (alias_count == ALIAS_SIZE) {
        fprintf(stderr, "alias: alias table full\n");
        return;
    }
    aliases[alias_count].name = strdup(name);
    aliases[alias_count].value = strdup(value);
    alias_count++;
}

char *get_alias(char *name)
{
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            return strdup(aliases[i].value);
        }
    }
    return NULL;
}

void print_aliases(void)
{
    for (int i = 0; i < alias_count; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}
