/*
 * File: task.c
 * Author: Pedro Lobo
 * Description: Contains functions related to the task struct.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj1.h"

/* Determines if dur a valid task duration
 * In order to be valid, it has to be a positive integer */
int
is_valid_task_duration(int dur) {
	return dur > 0;
}

/* Determines if des is a valid task description */
int
is_valid_task_description(char des[]) {

	/* Description can't be an emtpy string */
	return 1 <= strlen(des) && strlen(des) <= TASK_LEN;
}

/* Determines if a task exists, based on its id */
/* Task ids can be between 1 and the current number of tasks */
int
is_task_id(unsigned int id, data d[]) {
	return 1 <= id && id <= TASK_INDEX;
}

/* Determines if a task exists, based on its description */
int
is_task(char des[], data d[]) {
	unsigned int i;

	for (i = 0; i < TASK_INDEX; i++)
		if (!strcmp(TASK_DESCRIPTION(i), des))
			return TRUE;

	return FALSE;
}

/* Determines if the maximum number of tasks has been reached */
int
max_tasks(data d[]) {
	return TASK_INDEX == TASK_MAX;
}

/* Returns a id for a new task and increments the task index */
unsigned
get_new_id(data d[]) {
	increment_counter(1, 't', d);
	return TASK_INDEX;
}

/* Creates a new task, returning the id of the new task */
unsigned
create_task(data d[]) {
	unsigned id;

	/* If tasks are not sorted by id, sort them,
	 * so they can be indexed more easily */
	if (ORDER != 'i')
		mergesort(d, 0, TASK_INDEX - 1, 'i');

	id = get_new_id(d);
	TASK_ID(id - 1) = id;
	strcpy(TASK_ACTIVITY(id - 1), "TO DO");

	return id;
}

/* Returns the duration of the given task */
int
get_task_duration(unsigned id, data d[]) {
	/* If tasks are not sorted by id, sort them,
	 * so they can be indexed more easily */
	if (ORDER != 'i')
		mergesort(d, 0, TASK_INDEX - 1, 'i');

	return TASK_DURATION(id - 1);

}

/* Returns the description of the given task */
char *
get_task_description(unsigned id, data d[]) {
	/* If tasks are not sorted by id, sort them,
	 * so they can be indexed more easily */
	if (ORDER != 'i')
		mergesort(d, 0, TASK_INDEX - 1, 'i');

	return TASK_DESCRIPTION(id - 1);
}

/* Returns the activity of the given task */
char *
get_task_activity(unsigned id, data d[]) {
	/* If tasks are not sorted by id, sort them,
	 * so they can be indexed more easily */
	if (ORDER != 'i')
		mergesort(d, 0, TASK_INDEX - 1, 'i');

	return TASK_ACTIVITY(id - 1);
}

/* Returns the instant the task as been started */
unsigned
get_task_exec_time(unsigned id, data d[]) {
	/* If tasks are not sorted by id, sort them,
	 * so they can be indexed more easily */
	if (ORDER != 'i')
		mergesort(d, 0, TASK_INDEX - 1, 'i');

	return TASK_START_TIME(id - 1);
}

/* Gives the specified duration to the task with the given id */
void
set_task_duration(int dur, unsigned int id, data d[]) {
	/* If tasks are not sorted by id, sort them,
	 * so they can be indexed more easily */
	if (ORDER != 'i')
		mergesort(d, 0, TASK_INDEX - 1, 'i');

	TASK_DURATION(id - 1) = dur;
}

/* Gives the specified description to the task with the given id */
void
set_task_description(char des[], unsigned int id, data d[]) {
	/* If tasks are not sorted by id, sort them,
	 * so they can be indexed more easily */
	if (ORDER != 'i')
		mergesort(d, 0, TASK_INDEX - 1, 'i');

	strcpy(TASK_DESCRIPTION(id - 1), des);
}

/* Gives the specified activity to the task with the given id */
void
set_task_activity(char act[], unsigned int id, data d[]) {
	/* If tasks are not sorted by id, sort them,
	 * so they can be indexed more easily */
	if (ORDER != 'i')
		mergesort(d, 0, TASK_INDEX - 1, 'i');

	strcpy(TASK_ACTIVITY(id - 1), act);
}

void
set_task_start_time(unsigned int id, data d[]) {
	/* If tasks are not sorted by id, sort them,
	 * so they can be indexed more easily */
	if (ORDER != 'i')
		mergesort(d, 0, TASK_INDEX - 1, 'i');

	TASK_START_TIME(id - 1) = TIME;
}

/* Print all tasks by order, showing the id, activity, duration and description */
void
list_all_tasks(data d[]) {
	unsigned i;

	for (i = 0; i < TASK_INDEX; i++) {
		PRINT_TASK_INFO(TASK_ID(i), TASK_ACTIVITY(i),
				TASK_DURATION(i), TASK_DESCRIPTION(i));
	}
}
