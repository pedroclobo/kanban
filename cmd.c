#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

/* Prompts the user for a command to execute and saves it the string cmd */
void
get_full_cmd(char cmd[]) {
	fgets(cmd, CMD_LEN, stdin);
}

/* Returns the character that represents the command read from standart input */
char
get_cmd(char cmd[]) {
	return cmd[0];
}

/* Determines if the given command has no arguments */
int
is_no_arg_cmd(char cmd[]) {
	int i;

	/* A command string can contain spaces, tabs and newline chars */
	for (i = 1; cmd[i] != '\0'; i++)
		if (cmd[i] != ' ' && cmd[i] != '\n' && cmd[i] != '\t')
			return 0;

	return 'a' <= cmd[0] && cmd[0] <= 'z';
}
