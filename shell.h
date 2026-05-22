#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

char **split_line(char *line);
int execute(char **args);
char *get_path(char **env);
char *get_location(char *command, char **env);

#endif
