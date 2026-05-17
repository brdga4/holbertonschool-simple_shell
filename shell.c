#include "shell.h"

/**
 * split_line - splits a line into tokens
 * @line: the input line
 *
 * Return: array of strings
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
 * execute - forks and executes a command
 * @args: array of arguments
 *
 * Return: 1
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
			perror("hsh");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	return (1);
}
