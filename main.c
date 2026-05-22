#include "shell.h"

/**
 * run_cmd - Resolves and executes a command
 * @args: Parsed argument array
 * @line: Input line (to free if exiting)
 * @env: Environment variables
 * @prog_name: Name of the shell program (argv[0])
 *
 * Return: Exit status of the command
 */
static int run_cmd(char **args, char *line, char **env, char *prog_name)
{
	char *full_path;
	int status;

	full_path = get_location(args[0], env);
	if (full_path != NULL)
	{
		args[0] = full_path;
		status = execute(args);
		free(full_path);
		return (status);
	}

	fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
	status = 127;
	if (!isatty(STDIN_FILENO))
	{
		free(args);
		free(line);
		exit(status);
	}
	return (status);
}

/**
 * handle_builtins - Checks for and executes built-in commands
 * @args: Parsed argument array
 * @line: Input line (to free if exiting)
 * @env: Environment variables
 * @status: Current execution status
 *
 * Return: 1 if a built-in was executed, 0 otherwise
 */
static int handle_builtins(char **args, char *line, char **env, int status)
{
	int i;

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(status);
	}
	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; env[i] != NULL; i++)
			printf("%s\n", env[i]);
		free(args);
		return (1);
	}
	return (0);
}

/**
 * main - Entry point for the simple shell
 * @argc: Argument count (unused)
 * @argv: Argument vector (unused)
 * @env: Environment variables
 *
 * Return: Status of the last executed command
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	size_t len = 0;
	char **args;
	int status = 0;

	(void)argc;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "($) ", 4);
		if (getline(&line, &len, stdin) == -1)
			break;
		args = split_line(line);
		if (args != NULL && args[0] != NULL)
		{
			if (handle_builtins(args, line, env, status))
				continue;
			status = run_cmd(args, line, env, argv[0]);
		}
		if (args != NULL)
			free(args);
	}
	free(line);
	return (status);
}
