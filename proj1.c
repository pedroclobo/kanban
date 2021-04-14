#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

/* Time increments must be 0 or a positive integer */
int
is_valid_time(int dur) {
	return dur >= 0;
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


/* Recieves a command and separates it into relevant information to be used by other functions */
void
get_args(char cmd[], unsigned int *uint, char string1[], char string2[],
	 unsigned int ids[]) {
	switch (get_cmd(cmd)) {
	case NEW_TASK:
		sscanf(cmd, "%*2c %u %50[^\n]", uint, string1);
		break;
	case LIST_TASK:
		sscanf(cmd, "%*2c %[^\n]", string1);
		get_ids(string1, ids, uint);
		break;
	case FOWARD_TIME:
		sscanf(cmd, "%*2c %u", uint);
		break;
	case ADD_USER:
		sscanf(cmd, "%*2c %20[^ \n]", string1);
		break;
	case MOVE_TASK:
		sscanf(cmd, "%*2c %u %20[^ \n] %20[^\n]", uint, string1,
		       string2);
		break;
	case ADD_ACTIVITY:
		sscanf(cmd, "%*2c %20[^\n]", string1);
		break;
	case LIST_ACTIVITY_TASKS:
		sscanf(cmd, "%*2c %20[^\n]", string1);
		break;
	}
}

/* Adds a new task to the system, printing the task id */
void
new_task(int dur, char des[], data d[]) {
	unsigned int id;

	/* If task number limit is exceed */
	if (max_tasks(d))
		printf("too many tasks\n");

	/* If a task with the same description already exists */
	else if (is_task(des, d))
		printf("duplicate description\n");

	/* If the duration in not a postive integer */
	else if (!is_valid_task_duration(dur))
		printf("invalid duration\n");

	/* Create the new task */
	else if (is_valid_task_description(des)) {
		id = create_task(d);
		set_task_duration(dur, id, d);
		set_task_description(des, id, d);

		printf("task %u\n", id);
	}
}

/* Lists created tasks */
void
list_tasks(char cmd[], unsigned int ids[], unsigned int *size, data d[]) {
	unsigned int i;

	/* If command is passed with no arguments */
	if (is_no_arg_cmd(cmd)) {
		mergesort(d, 0, TASK_INDEX - 1, 'a', &d[0].order);
		list_all_tasks(d);
		return;
	}

	/* If command is passed with arguments */
	for (i = 0; i < *size; i++)
		if (!is_task_id(ids[i], d))
			printf("%u: no such task\n", ids[i]);

		else {
			printf("%u %.20s #%d %.50s\n",
			       ids[i],
			       get_task_activity(ids[i], d),
			       get_task_duration(ids[i], d),
			       get_task_description(ids[i], d));
		}
}


/* Foward the system time and prints current time */
void
foward_time(int dur, data d[]) {
	if (!is_valid_time(dur))
		printf("invalid time\n");

	else {
		increment_counter(dur, 'n', d);
		printf("%u\n", TIME);
	}
}


/* Adds a user or lists all users */
void
add_user(char cmd[], char user[], data d[]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < USER_INDEX; i++)
			printf("%.20s\n", d[0].u[i].name);

	/* Error handling */
	else if (is_user(user, d))
		printf("user already exists\n");

	else if (max_users(d))
		printf("too many users\n");

	/* Add new user */
	else if (is_valid_user_name(user))
		add_new_user(user, d);
}

/* Moves task from one activity to another */
void
move_task(unsigned id, char user[], char activity[], data d[]) {
	if (!is_task_id(id, d))
		printf("no such task\n");

	else if (!strcmp(activity, "TO DO")
		 && strcmp(get_task_activity(id, d), "TO DO"))
		printf("task already started\n");

	else if (!is_user(user, d))
		printf("no such user\n");

	else if (!is_activity(activity, d))
		printf("no such activity\n");

	else {

		/* Set start_time if activity is "TO DO" */
		if (!strcmp(get_task_activity(id, d), "TO DO"))
			set_task_start_time(id, d);

		/* Move task to activity */
		set_task_activity(activity, id, d);

		/* If task to move to is "DONE" */
		if (!strcmp(activity, "DONE")) {
			printf("duration=%u slack=%d\n",
			       TIME - get_task_exec_time(id, d),
			       TIME - get_task_exec_time(id, d) -
			       get_task_duration(id, d));
		}
	}
}

void
list_tasks_in_activity(char activity[], data d[]) {
	unsigned i;

	if (!is_activity(activity, d))
		printf("no such activity\n");

	else {
		mergesort(d, 0, TASK_INDEX - 1, 'd', &d[0].order);
		for (i = 0; i < TASK_INDEX; i++)
			if (!strcmp(d[0].t[i].act, activity))
				printf("%u %u %s\n",
				       d[0].t[i].id,
				       d[0].t[i].exec_time, d[0].t[i].des);
	}
}

void
add_activity(char cmd[], char des[], data d[]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < ACTIVITY_INDEX; i++)
			printf("%.20s\n", d[0].a[i].des);

	else {
		if (is_activity(des, d))
			printf("duplicate activity\n");
		else if (!is_valid_activity(des))
			printf("invalid description\n");
		else if (max_activities(d))
			printf("too many activities\n");
		else {
			add_new_activity(des, d);
		}
	}
}

int
main() {
	/* Declare data sctructure */
	data d;

	/* Declare command string */
	char cmd[CMD_LEN];
	unsigned int uint, ids[26];
	char string1[100];
	char string2[100];

	d.order = 'i';

	init_activities(&d);

	/* Counter */
	d.c.task = 0;
	d.c.time = 0;
	d.c.user = 0;
	d.c.activity = 3;

	/* While user doesn't quit the program */
	for (get_full_cmd(cmd); get_cmd(cmd) != EXIT; get_full_cmd(cmd)) {
		get_args(cmd, &uint, string1, string2, ids);
		switch (get_cmd(cmd)) {
		case NEW_TASK:
			new_task(uint, string1, &d);
			break;
		case LIST_TASK:
			list_tasks(cmd, ids, &uint, &d);
			break;
		case FOWARD_TIME:
			foward_time(uint, &d);
			break;
		case ADD_USER:
			add_user(cmd, string1, &d);
			break;
		case MOVE_TASK:
			move_task(uint, string1, string2, &d);
			break;
		case ADD_ACTIVITY:
			add_activity(cmd, string1, &d);
			break;
		case LIST_ACTIVITY_TASKS:
			list_tasks_in_activity(string1, &d);
			break;
		}
	}

	return 0;
}
