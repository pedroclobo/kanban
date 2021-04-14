#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

/* Determines if the maximum number of tasks has been reached */
int
max_tasks(data d[]) {
	return TASK_INDEX == TASK;
}

/* Returns a id for a new task and increments the task index */
unsigned
get_new_id(data d[]) {
	if (max_tasks(d))
		return EXIT_FAILURE;

	increment_counter(1, 't', d);
	return TASK_INDEX;
}

/* Determines if a task exists, based on its id */
/* Task ids are between 1 and the current number of tasks */
int
is_task_id(unsigned int id, data d[]) {
	return 1 <= id && id <= TASK_INDEX;
}

/* Determines if a task exists, based on its description */
int
is_task(char des[], data d[]) {
	unsigned int i;

	for (i = 0; i < TASK_INDEX; i++)
		if (!strcmp(d[0].t[i].des, des))
			return TRUE;

	return EXIT_SUCCESS;
}

/* Creates a new task, returning the id of the new task */
unsigned
create_task(data d[]) {
	unsigned id;

	if (ORDER != 'i')
		insertion(d, 0, TASK_INDEX - 1, 'i', &ORDER);

	id = get_new_id(d);
	d[0].t[id - 1].id = id;
	strcpy(d[0].t[id - 1].act, "TO DO");

	return id;
}

/* Returns the duration of the given task */
int
get_task_duration(unsigned id, data d[]) {
	if (ORDER != 'i')
		insertion(d, 0, TASK_INDEX - 1, 'i', &ORDER);

	return d[0].t[id - 1].dur;

}

/* Returns the description of the given task */
char *
get_task_description(unsigned id, data d[]) {
	if (ORDER != 'i')
		insertion(d, 0, TASK_INDEX - 1, 'i', &ORDER);

	return d[0].t[id - 1].des;
}

/* Returns the activity of the given task */
char *
get_task_activity(unsigned id, data d[]) {
	if (ORDER != 'i')
		insertion(d, 0, TASK_INDEX - 1, 'i', &ORDER);

	return d[0].t[id - 1].act;
}

/* Returns the instant the task as been started */
unsigned
get_task_exec_time(unsigned id, data d[]) {
	if (ORDER != 'i')
		insertion(d, 0, TASK_INDEX - 1, 'i', &ORDER);

	return d[0].t[id - 1].exec_time;
}

/* Gives the specified duration to the task with the given id */
void
set_task_duration(int dur, unsigned int id, data d[]) {
	if (ORDER != 'i')
		insertion(d, 0, TASK_INDEX - 1, 'i', &ORDER);

	d[0].t[id - 1].dur = dur;
}

/* Gives the specified description to the task with the given id */
void
set_task_description(char des[], unsigned int id, data d[]) {
	if (ORDER != 'i')
		insertion(d, 0, TASK_INDEX - 1, 'i', &ORDER);

	strcpy(d[0].t[id - 1].des, des);
}

/* Gives the specified activity to the task with the given id */
void
set_task_activity(char act[], unsigned int id, data d[]) {
	if (ORDER != 'i')
		insertion(d, 0, TASK_INDEX - 1, 'i', &ORDER);

	strcpy(d[0].t[id - 1].act, act);
}

void
set_task_start_time(unsigned int id, data d[]) {
	if (ORDER != 'i')
		insertion(d, 0, TASK_INDEX - 1, 'i', &ORDER);

	d[0].t[id - 1].exec_time = TIME;
}

/* Print all tasks by order */
void
list_all_tasks(data d[]) {
	unsigned i;

	for (i = 0; i < TASK_INDEX; i++) {
		printf("%u %s #%d %s\n",
		       d[0].t[i].id,
		       d[0].t[i].act, d[0].t[i].dur, d[0].t[i].des);
	}
}
