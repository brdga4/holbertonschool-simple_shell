#include "shell.h"

/**
 * find_path - Finds full path of a command using PATH
 * @cmd: the command name
 *
 * Return: full path string (must be freed), or NULL
 */
char *find_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full_path;
	struct stat st;
	size_t len;

	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0 && (st.st_mode & S_IXUSR))
			return (strdup(cmd));
		return (NULL);
	}

	path_env = getenv("PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, cmd);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * tokenize - Splits a line into tokens
 * @line: input string
 *
 * Return: NULL-terminated array of strings
 */
char **tokenize(char *line)
{
	char **tokens;
	char *token, *line_copy;
	int count = 0, i = 0;

	line_copy = strdup(line);
	if (!line_copy)
		return (NULL);

	token = strtok(line_copy, " \t");
	while (token)
	{
		count++;
		token = strtok(NULL, " \t");
	}
	free(line_copy);

	if (count == 0)
		return (NULL);

	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);

	token = strtok(line, " \t");
	while (token)
	{
		tokens[i++] = token;
		token = strtok(NULL, " \t");
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * execute - Forks and executes a command
 * @args: NULL-terminated argument array
 * @prog_name: name of the shell program
 *
 * Return: exit status of child
 */
int execute(char **args, char *prog_name)
{
	pid_t pid;
	int status;
	char *path;
	static int cmd_num = 1;

	path = find_path(args[0]);
	if (!path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, cmd_num++, args[0]);
		return (127);
	}
	cmd_num++;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror(prog_name);
			free(path);
			exit(127);
		}
	}

	waitpid(pid, &status, 0);
	free(path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
