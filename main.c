#include "shell.h"

/**
 * main - Entry point for simple shell
 *
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	char **args;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "($) ", 4);
		if (getline(&line, &len, stdin) == -1)
			break;
		args = split_line(line);
		if (args[0] != NULL)
			execute(args);
		free(args);
	}
	free(line);
	return (0);
}
