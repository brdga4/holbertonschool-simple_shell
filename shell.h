#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

char *find_path(char *cmd);
char **tokenize(char *line);
int execute(char **args, char *prog_name);
int handle_builtin(char **args, char *prog_name, char *line, int status);
int run_shell(char *argv[]);

#endif
