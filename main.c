#include "shell.h"

int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	size_t len = 0;
	char **args;
	char *full_path;
	int status = 0;
	int i;
	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "($) ", 4);

		if (getline(&line, &len, stdin) == -1)
			break;

		args = split_line(line);

		if (args != NULL && args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free(args);
				free(line);
				exit(status);
			}

			if (strcmp(args[0], "env") == 0)
			{
				for (i = 0; env[i] != NULL; i++)
				{
					printf("%s\n", env[i]);
				}
				free(args);
				continue;
			}

			full_path = get_location(args[0], env);

			if (full_path != NULL)
			{
				args[0] = full_path;
				status = execute(args);
				free(full_path);
			}
			else
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
				status = 127;
				if (!isatty(STDIN_FILENO))
				{
					free(args);
					free(line);
					exit(status);
				}
			}
		}
		if (args != NULL)
			free(args);
	}
	free(line);
	return (status);
}
