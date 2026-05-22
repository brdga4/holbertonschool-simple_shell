#include "shell.h"

/**
 * split_line - splits a line into tokens
 * @line: the input line
 *
 * Return: array of strings, or NULL on failure
 */
char **split_line(char *line)
{
	int i = 0;
	char **tokens = malloc(64 * sizeof(char *));
	char *token;

	if (!tokens)
		return (NULL);
	token = strtok(line, " \t\n");
	while (token != NULL)
	{
		tokens[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute - finds and executes a command
 * @args: array of arguments
 * @progname: name of the shell program (argv[0])
 *
 * Return: 1 on success, 0 if command not found
 */
int execute(char **args, char *progname)
{
	pid_t pid;
	int status;
	char *fullpath;

	fullpath = find_path(args[0]);
	if (fullpath == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", progname, args[0]);
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(fullpath, args, environ) == -1)
			perror(progname);
		if (fullpath != args[0])
			free(fullpath);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	if (fullpath != args[0])
		free(fullpath);
	return (1);
}
