#include "shell.h"

/**
 * handle_builtin - Handles builtin commands
 * @args: argument array
 * @prog_name: program name
 * @line: input line to free
 * @status: last exit status
 *
 * Return: 1 if builtin handled, 0 otherwise
 */
int handle_builtin(char **args, char *prog_name, char *line, int status)
{
	int i = 0;

	(void)prog_name;
	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(status);
	}
	if (strcmp(args[0], "env") == 0)
	{
		while (environ[i])
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return (1);
	}
	return (0);
}

/**
 * run_shell - Main shell loop
 * @argv: argument vector
 *
 * Return: exit status
 */
int run_shell(char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	int status = 0;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(status);
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (line[0] == '\0')
			continue;
		args = tokenize(line);
		if (args == NULL)
			continue;
		if (handle_builtin(args, argv[0], line, status))
		{
			free(args);
			continue;
		}
		status = execute(args, argv[0]);
		free(args);
	}
	free(line);
	return (status);
}

/**
 * main - Entry point for the shell
 * @argc: argument count (unused)
 * @argv: argument vector
 *
 * Return: exit status
 */
int main(int argc __attribute__((unused)), char *argv[])
{
	return (run_shell(argv));
}
