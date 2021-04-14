#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

/* Determines if a activity exists */
int
is_activity(char act[], data d[]) {
	unsigned int i;

	for (i = 0; i < ACTIVITY_INDEX; i++)
		if (!strcmp(d[0].a[i].des, act))
			return 1;

	return 0;
}

/* Determines if the input is a valid activity description */
int
is_valid_activity(char des[]) {
	int i;

	for (i = 0; des[i] != '\0'; i++)
		/* Activity description should not contain lowercase letters */
		if ('a' <= des[i] && des[i] <= 'z')
			return 0;

	return 1;
}

/* Determines if the maximum number of activities has been reached */
int
max_activities(data d[]) {
	return ACTIVITY_INDEX == ACT;
}

/* Recieves a activity and adds it to the system, if the maximum number
 * of activities has not been reached */
void
add_new_activity(char des[], data d[]) {
	if (!max_activities(d)) {
		strcpy(d[0].a[ACTIVITY_INDEX].des, des);
		increment_counter(1, 'a', d);
	}
}
