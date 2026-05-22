#include "shell.h"

/**
 * find_path - searches for a command in PATH directories
 * @cmd: the command name
 *
 * Return: full path if found (caller must free),
 *         cmd itself if it contains '/',
 *         NULL if not found
 */
char *find_path(char *cmd)
{
	char *path_env, *path_copy, *dir;
	char fullpath[1024];
	struct stat st;

	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	path_env = getenv("PATH");
	if (path_env == NULL || path_env[0] == '\0')
		return (NULL);
	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		sprintf(fullpath, "%s/%s", dir, cmd);
		if (stat(fullpath, &st) == 0)
		{
			free(path_copy);
			return (strdup(fullpath));
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
