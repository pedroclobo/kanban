/*
 * File: proj1.c
 * Author: Pedro Lobo
 * Description: File with all high-level functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj1.h"

/* Adds a new task to the system, printing the task id */
void
new_task(int dur, char des[], data d[]) {
	unsigned int id;

	/* If task number limit is exceed */
	if (max_tasks(d))
		printf(ERROR_TOO_MANY_TASKS);

	/* If a task with the same description already exists */
	else if (is_task(des, d))
		printf(ERROR_DUPLICATE_DESCRIPTION);

	/* If the duration in not a postive integer */
	else if (!is_valid_task_duration(dur))
		printf(ERROR_INVALID_DURATION);

	/* Create the new task */
	else if (is_valid_task_description(des)) {
		id = create_task(d);
		set_task_duration(dur, id, d);
		set_task_description(des, id, d);

		printf(PRINT_TASK_ID(id));
	}
}

/* Lists created tasks */
void
list_tasks(char cmd[], unsigned int ids[], unsigned int *size, data d[]) {
	unsigned int i;

	/* If command is passed with no arguments */
	if (is_no_arg_cmd(cmd)) {
		mergesort(d, 0, TASK_INDEX - 1, 'a');
		list_all_tasks(d);
		return;
	}

	/* If command is passed with arguments */
	for (i = 0; i < *size; i++)
		if (!is_task_id(ids[i], d))
			printf(ERROR_NO_SUCH_TASK(ids[i]));

		else {
			printf(PRINT_TASK_INFO(ids[i],
					       get_task_activity(ids[i], d),
					       get_task_duration(ids[i], d),
					       get_task_description(ids[i],
								    d)));
		}
}


/* Foward the system time and prints current time */
void
foward_time(int dur, data d[]) {
	if (!is_valid_time(dur))
		printf(ERROR_INVALID_TIME);

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
			printf("%s\n", USER_NAME(i));

	/* Error handling */
	else if (is_user(user, d))
		printf(ERROR_USER_ALREADY_EXISTS);

	else if (max_users(d))
		printf(ERROR_TOO_MANY_USERS);

	/* Add new user */
	else if (is_valid_user_name(user))
		add_new_user(user, d);
}

/* Moves task from one activity to another */
void
move_task(unsigned id, char user[], char activity[], data d[]) {
	if (!is_task_id(id, d))
		printf(ERROR_NO_SUCH_TASK_NO_ARG);

	/* When moving a started "TO DO" to "TO DO" */
	else if (!strcmp(activity, "TO DO")
		 && strcmp(get_task_activity(id, d), "TO DO"))
		printf(ERROR_TASK_ALREADY_STARTED);

	else if (!is_user(user, d))
		printf(ERROR_NO_SUCH_USER);

	else if (!is_activity(activity, d))
		printf(ERROR_NO_SUCH_ACTIVITY);

	else {

		/* Set start_time if activity is "TO DO" */
		if (!strcmp(get_task_activity(id, d), "TO DO"))
			set_task_start_time(id, d);

		/* Move task to activity */
		set_task_activity(activity, id, d);

		/* If task to move to is "DONE" */
		if (!strcmp(activity, "DONE")) {
			printf(PRINT_TASK_DURATION_SLACK(TIME -
							 get_task_exec_time(id,
									    d),
							 TIME -
							 get_task_exec_time(id,
									    d) -
							 get_task_duration(id,
									   d)));
		}
	}
}

/* List all tasks in the activity */
void
list_tasks_in_activity(char activity[], data d[]) {
	unsigned i;

	if (!is_activity(activity, d))
		printf(ERROR_NO_SUCH_ACTIVITY);

	else {

		/* Order tasks by start time and description */
		mergesort(d, 0, TASK_INDEX - 1, 'd');

		/* Print tasks in the activity */
		for (i = 0; i < TASK_INDEX; i++)
			if (!strcmp(TASK_ACTIVITY(i), activity))
				printf("%u %u %s\n",
				       TASK_ID(i),
				       TASK_START_TIME(i), TASK_DESCRIPTION(i));
	}
}

/* Adds an activity with description des or lists all activities */
void
add_activity(char cmd[], char des[], data d[]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < ACTIVITY_INDEX; i++)
			printf("%s\n", ACTIVITY_DESCRIPTION(i));

	else {
		if (is_activity(des, d))
			printf(ERROR_DUPLICATE_ACTIVITY);

		else if (!is_valid_activity(des))
			printf(ERROR_INVALID_DESCRIPTION);

		else if (max_activities(d))
			printf(ERROR_TOO_MANY_ACTIVITIES);

		else {
			add_new_activity(des, d);
		}
	}
}

int
main() {
	/* Holds all the vectors and counters */
	data d;

	/* Saves the command read from stdin */
	char cmd[CMD_LEN];

	/* Strings and unsigned vectors to get information from stdin */
	unsigned int uint, ids[CMD_LEN];
	char string1[CMD_LEN];
	char string2[CMD_LEN];

	/* Tasks are sorted by id by default */
	change_order_char(&d, 'i');

	/* Initialize time and counters */
	init_time(&d);
	init_counters(&d);

	/* Add default activities */
	init_activities(&d);

	/* While user doesn't quit the program */
	for (get_full_cmd(cmd); get_cmd(cmd) != EXIT; get_full_cmd(cmd)) {
		get_args(cmd, &uint, string1, string2, ids);

		if (get_cmd(cmd) == NEW_TASK)
			new_task(uint, string1, &d);

		else if (get_cmd(cmd) == LIST_TASK)
			list_tasks(cmd, ids, &uint, &d);

		else if (get_cmd(cmd) == FOWARD_TIME)
			foward_time(uint, &d);

		else if (get_cmd(cmd) == ADD_USER)
			add_user(cmd, string1, &d);

		else if (get_cmd(cmd) == MOVE_TASK)
			move_task(uint, string1, string2, &d);

		else if (get_cmd(cmd) == ADD_ACTIVITY)
			add_activity(cmd, string1, &d);

		else if (get_cmd(cmd) == LIST_ACTIVITY_TASKS)
			list_tasks_in_activity(string1, &d);
	}

	return EXIT_SUCCESS;
}
