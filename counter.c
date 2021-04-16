/*
 * File: counter.c
 * Author: Pedro Lobo
 * Description: File with all functions related to the counter struct.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj1.h"

/* Initialize counters */
void
init_counters(data d[]) {
	TASK_INDEX = 0;
	ACTIVITY_INDEX = 0;
	USER_INDEX = 0;
}

/* Increments the counters by the specified increment (inc) */
void
increment_counter(unsigned inc, char type, data d[]) {
	/* Increment task index */
	if (type == 't')
		TASK_INDEX += inc;

	/* Increment system time */
	else if (type == 'n')
		TIME += inc;

	/* Increment user index */
	else if (type == 'u')
		USER_INDEX += inc;

	/* Increment activity index */
	else if (type == 'a')
		ACTIVITY_INDEX += inc;
}
