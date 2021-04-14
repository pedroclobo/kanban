#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

/* Determines if the input is a valid activity description */
int
is_valid_activity(char des[]) {
	int i;

	for (i = 0; des[i] != '\0'; i++)
		/* Activity description must not contain lowercase letters */
		if ('a' <= des[i] && des[i] <= 'z')
			return 0;

	/* Activity description must not be a empty string */
	return 1 <= strlen(des) && strlen(des) <= ACTIVITY_LEN;
}

/* Determines if a activity exists, based on its description */
int
is_activity(char des[], data d[]) {
	unsigned int i;

	for (i = 0; i < ACTIVITY_INDEX; i++)
		if (!strcmp(d[0].a[i].des, des))
			return 1;

	return 0;
}

/* Determines if the maximum number of activities has been reached */
int
max_activities(data d[]) {
	return ACTIVITY_INDEX == ACTIVITY_MAX;
}

/* Recieves a activity and adds it to the system, if the maximum number of
 * activities has not been reached */
void
add_new_activity(char des[], data d[]) {
	if (!max_activities(d) && is_valid_activity(des)) {
		strcpy(d[0].a[ACTIVITY_INDEX].des, des);
		increment_counter(1, 'a', d);
	}
}

void
init_activities(data d[]) {
	/* Start activity vector index at 0 */
	ACTIVITY_INDEX = 0;

	/* Add default activities */
	add_new_activity("TO DO", d);
	add_new_activity("IN PROGRESS", d);
	add_new_activity("DONE", d);
}
