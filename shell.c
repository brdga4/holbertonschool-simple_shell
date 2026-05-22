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
		{
			perror("hsh");
			exit(2);
		}
	}
	else if (pid < 0)
	{
		perror("hsh");
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
	}
	return (0);
}

/**
 * get_path - Finds the PATH variable in the environment array
 * @env: The environment variables array
 *
 * Return: Pointer to the path value, or NULL if not found
 */
char *get_path(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' &&
		    env[i][2] == 'T' && env[i][3] == 'H' && env[i][4] == '=')
		{
			return (&env[i][5]);
		}
	}
	return (NULL);
}

/**
 * get_location - Looks for a command in the directories listed in PATH
 * @command: The command to look for
 *
 * Return: Full path of the command if found, or NULL if not found
 */
char *get_location(char *command, char **env)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &buffer) == 0)
		{
			path_copy = malloc(strlen(command) + 1);
			if (!path_copy)
				return (NULL);
			strcpy(path_copy, command);
			return (path_copy);
		}
		return (NULL);
	}

	path = get_path(env);
	if (!path || strlen(path) == 0)
		return (NULL);

	path_copy = malloc(strlen(path) + 1);
	if (!path_copy)
		return (NULL);
	strcpy(path_copy, path);

	command_length = strlen(command);
	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		directory_length = strlen(path_token);
		file_path = malloc(command_length + directory_length + 2);
		if (!file_path)
		{
			free(path_copy);
			return (NULL);
		}

		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, command);

		if (stat(file_path, &buffer) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		free(file_path);
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
