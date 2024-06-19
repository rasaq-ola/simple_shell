char *read_line(FILE *input)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    nread = getline(&line, &bufsize, input);
    if (nread == -1) {
        free(line);
        return (NULL);
    }
    return (line);
}
