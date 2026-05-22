# C - Simple Shell

## Description
This repository contains a basic UNIX command-line interpreter, developed as a milestone project for the Holberton School low-level programming curriculum. 

The `hsh` shell is a simplified mimic of the standard `sh`. It reads commands from standard input, parses them, resolves their execution paths using the environment `PATH` variable, and executes them in child processes. The project is strictly compliant with the Betty coding style and has been thoroughly tested for memory leaks using Valgrind.

## Repository Contents

| File | Description |
| --- | --- |
| `main.c` | Program entry point. Contains the interactive/non-interactive loops, built-in execution logic, and error handling. |
| `shell.c` | Core logic. Contains functions for tokenization (`split_line`), `PATH` resolution (`get_location`), and child process execution (`execute`). |
| `shell.h` | Header file containing necessary standard libraries, structures, and function prototypes. |
| `man_1_simple_shell` | Standard manual page documenting the shell's usage, features, and exit statuses. |

## Requirements
* Operating System: Ubuntu 20.04 LTS
* Compiler: `gcc`
* Compilation flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`

## Compilation
To compile the shell, run the following command at the root of the repository:

    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Usage

The shell can operate in two modes:

### 1. Interactive Mode
When executed directly in the terminal, the shell will display a prompt `($)` and wait for user input.

    $ ./hsh
    ($) /bin/ls
    hsh main.c shell.c shell.h
    ($) exit
    $

### 2. Non-Interactive Mode
When commands are piped or redirected into the program, it will execute them silently without displaying the prompt.

    $ echo "/bin/ls" | ./hsh
    hsh main.c shell.c shell.h
    $
    $ cat test_ls | ./hsh
    hsh main.c shell.c shell.h
    $

## Built-In Commands
The shell currently supports the following built-in commands:
* `exit`: Terminates the shell. Exits with the status of the last executed command.
* `env`: Prints the environment variables to the standard output.

## Error Handling
If a command cannot be found, `hsh` prints an error exactly matching standard `sh` behavior, utilizing `argv[0]` to display the executable name.

    $ echo "qwerty" | ./hsh
    ./hsh: 1: qwerty: not found

## Authors
* Shahad Alharbi <shahadeissa111@gmail.com>
* Basem Tashkandi <basem.tashkandi@gmail.com>
