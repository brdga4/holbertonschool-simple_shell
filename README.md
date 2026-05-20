 Simple Shell

A simple UNIX command line interpreter written in C.

## Description

This is a simple shell that mimics the behavior of /bin/sh.
It was built as a project at Holberton School.

## Compilation

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Usage

### Interactive mode:
./hsh
($) /bin/ls
($) exit

### Non-interactive mode:
echo "/bin/ls" | ./hsh

## Requirements

- Ubuntu 20.04 LTS
- gcc compiler

## Authors

Shahad Alharbi shahadeissa111@gmail.com
Basem

