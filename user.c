/*
 * File: user.c
 * Author: Pedro Lobo
 * Description: File with all functions related to the user struct.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj1.h"

/* Determines if user in a valid user name */
int
is_valid_user_name(char user[]) {
	int i;

	/* User name can't contain whitespaces */
	for (i = 0; user[i] != '\0'; i++)
		if (user[i] == ' ' || user[i] == '\t')
			return FALSE;

	/* User name can't be an empty string */
	return 1 <= strlen(user) && strlen(user) <= USER_LEN;
}

/* Determines if a user exists */
int
is_user(char user[], data d[]) {
	unsigned int i;

	for (i = 0; i < USER_INDEX; i++)
		if (!strcmp(USER_NAME(i), user))
			return TRUE;

	return FALSE;
}

/* Determines if the maximum number of users has been reached */
int
max_users(data d[]) {
	return USER_INDEX == USER_MAX;
}

/* Recieves a username and adds it to the system, if the maximum number
 * of users has not been reached and user is a valid user name*/
void
add_new_user(char user[], data d[]) {
	if (!max_users(d) && is_valid_user_name(user)) {
		strcpy(USER_NAME(USER_INDEX), user);

		/* Increment user indexer */
		increment_counter(1, 'u', d);
	}
}
