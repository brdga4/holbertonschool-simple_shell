#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

char **split_line(char *line);
int execute(char **args, char *progname);
char *find_path(char *cmd);

#endif
