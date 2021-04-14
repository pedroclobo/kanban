#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

int
is_valid_user_name(char user[]) {
	return 1 <= strlen(user) && strlen(user) <= USER;
}

/* Determines if a user exists */
int
is_user(char user[], data d[]) {
	unsigned int i;

	for (i = 0; i < USER_INDEX; i++)
		if (!strcmp(d[0].u[i].name, user))
			return 1;

	return 0;
}

/* Determines if the maximum number of users has been reached */
int
max_users(data d[]) {
	return USER_INDEX == USER;
}

/* Recieves a username and adds it to the system, if the maximum number
 * of users has not been reached */
void
add_new_user(char user[], data d[]) {
	if (!max_users(d)) {
		strcpy(d[0].u[USER_INDEX].name, user);
		increment_counter(1, 'u', d);
	}
}
