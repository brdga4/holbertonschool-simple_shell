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
 * Return: Exit status of the child process
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
 * search_path - Searches directories in PATH for the command
 * @path_copy: A copy of the PATH string
 * @command: The command to find
 *
 * Return: Full path of command, or NULL if not found
 */
static char *search_path(char *path_copy, char *command)
{
	char *path_token, *file_path;
	int cmd_len, dir_len;
	struct stat buffer;

	cmd_len = strlen(command);
	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		dir_len = strlen(path_token);
		file_path = malloc(cmd_len + dir_len + 2);
		if (!file_path)
			return (NULL);

		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, command);

		if (stat(file_path, &buffer) == 0)
			return (file_path);

		free(file_path);
		path_token = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * get_location - Looks for a command in the directories listed in PATH
 * @command: The command to look for
 * @env: The environment variables array
 *
 * Return: Full path of the command if found, or NULL if not found
 */
char *get_location(char *command, char **env)
{
	char *path, *path_copy, *file_path;
	struct stat buffer;

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &buffer) == 0)
		{
			path_copy = malloc(strlen(command) + 1);
			if (path_copy)
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

	file_path = search_path(path_copy, command);
	free(path_copy);

	return (file_path);
}
