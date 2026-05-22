#include "shell.h"

/**
 * main - Entry point for simple shell
 * @argc: argument count (unused)
 * @argv: argument vector
 *
 * Return: 0
 */
int main(int argc __attribute__((unused)), char **argv)
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
		if (args != NULL && args[0] != NULL)
			execute(args, argv[0]);
		free(args);
	}
	free(line);
	return (0);
}
