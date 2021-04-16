/*
 * File: stdin.c
 * Author: Pedro Lobo
 * Description: File with all functions to process input from stdin.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj1.h"

/* Prompts the user for a command to execute and saves it the string cmd */
void
get_full_cmd(char cmd[]) {
	fgets(cmd, CMD_LEN, stdin);
}

/* Returns the character that represents the command read from stdin */
char
get_cmd(char cmd[]) {
	return cmd[0];
}

/* Determines if the given command has no arguments */
int
is_no_arg_cmd(char cmd[]) {
	int i;

	/* A command with no arguments can only contain spaces, tabs and newline caracters */
	for (i = 1; cmd[i] != '\0'; i++)
		if (cmd[i] != ' ' && cmd[i] != '\n' && cmd[i] != '\t')
			return 0;

	return 'a' <= cmd[0] && cmd[0] <= 'z';
}

/* Transforms a string of ids separated by whitespaces into an array of ids */
void
get_ids(char cmd[], unsigned ids[], unsigned *size) {
	unsigned i, number = 0;

	/* Builds the number and places it in the array */
	for (i = 0, *size = 0; cmd[i] != '\0'; i++) {
		if (cmd[i] >= '0' && cmd[i] <= '9')
			number = 10 * number + (cmd[i] - '0');
		else if (cmd[i] == ' ') {
			ids[*size] = number;
			*size += 1;
			number = 0;
		}
	}

	/* The final number has to be added manually because there's no " " at the end of the string */
	ids[*size] = number;
	*size += 1;
}

/* Recieves a command and separates it into relevant information,
 * depending on the command, to be used by the other functions */
void
get_args(char cmd[], unsigned int *uint, char string1[], char string2[],
	 unsigned int ids[]) {
	if (get_cmd(cmd) == NEW_TASK)
		sscanf(cmd, "%*2c %u %50[^\n]", uint, string1);

	else if (get_cmd(cmd) == LIST_TASK) {
		sscanf(cmd, "%*2c %[^\n]", string1);
		get_ids(string1, ids, uint);
	}

	else if (get_cmd(cmd) == FOWARD_TIME)
		sscanf(cmd, "%*2c %u", uint);

	else if (get_cmd(cmd) == ADD_USER)
		sscanf(cmd, "%*2c %20[^ \n]", string1);

	else if (get_cmd(cmd) == MOVE_TASK)
		sscanf(cmd, "%*2c %u %20[^ \n] %20[^\n]", uint, string1,
		       string2);

	else if (get_cmd(cmd) == ADD_ACTIVITY)
		sscanf(cmd, "%*2c %20[^\n]", string1);

	else if (get_cmd(cmd) == LIST_ACTIVITY_TASKS)
		sscanf(cmd, "%*2c %20[^\n]", string1);
}
