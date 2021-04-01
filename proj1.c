# include <stdio.h>
# include <string.h>

# include "definitions.h"

/* Prompts the user for a command to
 * execute and saves it to a string */
void get_cmd(char cmd[]) {
	printf("? ");
	fgets(cmd, CMD_LEN, stdin);
}

/* Returns the name of the command
 * represented by the given string */
char get_cmd_name(char cmd[]) {
	return cmd[0];
}

/* Determines if the given command has no arguments */
int is_no_arg_cmd(char cmd[]) {
	return (strlen(cmd) == 2);
}

/* Increments the counter */
void increment_counter(double inc, counter c[], char type) {
	switch (type) {
		case 't':
			c[0].task += inc;
			break;
		case 'n':
			c[0].time += inc;
			break;
		case 'u':
			c[0].user += inc;
			break;
		case 'a':
			c[0].activity += inc;
			break;
	}
}

/* Determines if a user exists */
int is_user(char user[], char users[][USER_LEN], counter c[]) {
	unsigned int i;

	for (i = 0; i < c[0].user; i++)
		if (!strcmp(users[i], user))
			return 1;

	return 0;
}

/* Determines if a activity exists */
int is_activity(char act[], char activities[][ACT_LEN], counter c[]) {
	unsigned int i;

	for (i = 0; i < c[0].activity; i++)
		if (!strcmp(activities[i], act))
			return 1;

	return 0;
}

/* Determines if a task exists, based on its id */
int is_task_id(unsigned int id, counter c[]) {
	return 1 <= id && id <= c[0].task;
}

/* Determines if a task exists, based on its description */
int is_task(char des[], task tasks[], counter c[]) {
	unsigned int i;

	for (i = 0; i < c[0].task; i++)
		if (!strcmp(tasks[i].des, des))
			return 1;

	return 0;
}

/* Determines if the input is a valid task duration */
int is_valid_duration(unsigned int dur) {
	return dur > 0;
}

/* Determines if the input is a valid time increment */
int is_valid_time(double dur) {
	return dur >= 0;
}

int is_valid_activity(char des[]) {
	int i;

	for (i = 0; des[i] != '\0'; i++)
		if ('a' <= des[i] && des[i] <= 'z')
			return 0;

	return 1;
}

/* Determines if the maximum number of tasks has been reached */
int max_tasks(counter c[]) {
	return c[0].task == TASK;
}

/* Determines if the maximum number of users has been reached */
int max_users(counter c[]) {
	return c[0].user == USER;
}

int max_activities(counter c[]) {
	return c[0].activity == ACT;
}

/* Gives the specified duration to the task with the given id */
void add_task_duration(unsigned int dur, unsigned int id, task tasks[]) {
	tasks[id-1].dur = dur;
}

/* Gives the specified description to the task with the given id */
void add_task_description(char des[], unsigned int id, task tasks[]) {
	strcpy(tasks[id-1].des, des);
}

/* Gives the specified activity to the task with the given id */
void add_task_activity(char act[], unsigned int id, task tasks[]) {
	strcpy(tasks[id-1].act, act);
}

void get_task_duration(unsigned int id, unsigned int *dur, task tasks[]) {
	*dur = tasks[id-1].dur;
}

void get_task_description(unsigned int id, char des[], task tasks[]) {
	strcpy(des, tasks[id-1].des);
}

void get_task_activity(unsigned int id, char act[], task tasks[]) {
	strcpy(act, tasks[id-1].act);
}

/* Sugests a task id for a new task */
void get_new_id(unsigned int *id, counter c[]) {
	if (!max_tasks(c)) {
		*id = c[0].task + 1;
		increment_counter(1, c, 't');
	}
}

void add_new_user(char user[], char users[][USER_LEN], counter c[]) {
	if (!max_users(c)) {
		strcpy(users[c[0].user], user);
		increment_counter(1, c, 'u');
	}
}

void add_new_activity(char des[], char activities[][ACT_LEN], counter c[]) {
	if (!max_activities(c)) {
		strcpy(activities[c[0].activity], des);
		increment_counter(1, c, 'a');
	}
}

/* Recieves string of tasks ids and
 * converts it to an array of tasks ids */
void get_ids(char cmd[], unsigned int ids[], unsigned int *size) {
	unsigned int i, number = 0;

	/* Builds the number and places it in the array */
	for (i = 0, *size = 0; cmd[i] != '\0'; i++) {
		if (cmd[i] >= '0' && cmd[i] <= '9')
			number = 10*number + (cmd[i] - '0');
		else if (cmd[i] == ' '){
			ids[*size] = number;
			*size += 1;
			number = 0;
		}
	}
	/* The final number has to be added manually
	 * because there's no " " at the end of the string */
	ids[*size] = number;
	*size += 1;
}

void get_args(char cmd[], unsigned int *dur, char des[], char act[], char user[], unsigned int ids[], unsigned int *size, unsigned int *id) {
	char ids_str[26];

	switch(get_cmd_name(cmd)) {
		case NEW_TASK:
			sscanf(cmd, "%*2c %u %[^\n]", dur, des);
			strcpy(act, "TO DO");
			break;
		case LIST_TASK:
			sscanf(cmd, "%*2c %[^\n]", ids_str);
			get_ids(ids_str, ids, size);
			break;
		case FOWARD_TIME:
			sscanf(cmd, "%*2c %u", dur);
			break;
		case ADD_USER:
			sscanf(cmd, "%*2c %[^\n]", user);
			break;
		case MOVE_TASK:
			sscanf(cmd, "%u %[^ ] %[^\n]", id, user, act);
			break;
		case ADD_ACTIVITY:
			sscanf(cmd, "%*2c %[^\n]", des);
			break;
	}
}

/* Adds a new task to the system,
 * printing the task id */
void new_task(unsigned int dur, char des[], counter c[], task tasks[]) {
	unsigned int id;

	/* Get a id for the new task */
	get_new_id(&id, c);

	/* If task number limit is exceed */
	if (max_tasks(c))
		printf("too many tasks\n");

	/* If a task with the same description already exists */
	else if (is_task(des, tasks, c))
		printf("duplicate description\n");

	/* If the duration in not a postive integer */
	else if (!is_valid_duration(dur))
		printf("invalid duration\n");

	/* Create the new task */
	else {
		add_task_duration(dur, id, tasks);
		add_task_description(des, id, tasks);
		add_task_activity("TO DO", id, tasks);

		printf("task %u\n", id);
	}
}

/* Lists created tasks */
void list_tasks(char cmd[], unsigned int ids[], unsigned int *size, task tasks[], counter c[]) {
	unsigned int id;
	unsigned int dur;
	char des[TASK_LEN];
	char act[ACT_LEN];

	int ERROR = NO;

	/* If no arguments are specified, list all tasks */
	if (is_no_arg_cmd(cmd))
		for (id = 1; id <= c[0].task; id++) {
			get_task_duration(id, &dur, tasks);
			get_task_description(id, des, tasks);
			get_task_activity(id, act, tasks);
			printf("%u %s #%u %s\n", id, act, dur, des);
		}

	else {
		/* Task id validation */
		for (id = 1; id < *size+1; id++)
			if (!is_task_id(ids[id-1], c)) {
				printf("%u no such task\n", ids[id-1]);
				ERROR = YES;
			}

		/* If all ids are valid, list the tasks */
		if (ERROR == NO) {
			for (id = 1; id < *size+1; id++) {
				get_task_duration(id, &dur, tasks);
				get_task_description(id, des, tasks);
				get_task_activity(id, act, tasks);
				printf("%u %s #%u %s\n", id, act, dur, des);
			}
		}
	}
}


/* Foward the system time and prints current time */
void foward_time(int dur, counter c[]) {
	if (!is_valid_time(dur))
		printf("invalid time\n");

	else {
		increment_counter(dur, c, 't');
		c[0].time += dur;
		printf("%u\n", c[0].time);
	}
}


/* Adds a user or lists all users */
void add_user(char cmd[], char user[], counter c[], char users[][USER_LEN]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < c[0].user; i++)
			printf("%s\n", users[i]);

	else {
		/* Errors */
		if (is_user(user, users, c))
			printf("user already exists\n");
		else if (max_users(c))
			printf("too many users\n");

		/* If there are no errors */
		else {
			if (is_no_arg_cmd(cmd))
				for (i = 0; i < c[0].user; i++)
					printf("%s\n", users[i]);
			else
				add_new_user(user, users, c);
		}
	}
}

/* Moves task from one activity to another */
void move_task(unsigned int id, char user[], char activity[], task tasks[], char users[][USER_LEN], counter c[], char activities[][ACT_LEN]) {
	if (!is_task_id(id, c))
		printf("no such task\n");

	else if (!strcmp(activity, "TO DO"))
		printf("task already started\n");

	else if (!is_user(user, users, c))
		printf("no such user\n");

	else if (!is_activity(activity, activities, c))
		printf("no such activity\n");

	else {
		add_task_activity(activity, id, tasks);
	}
}


void add_activity(char cmd[], char des[], char activities[][ACT_LEN], counter c[]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < c[0].activity; i++)
			printf("%s\n", activities[i]);

	else {
		if (is_activity(des, activities, c))
			printf("duplicate activity\n");
		else if (!is_valid_activity(des))
			printf("invalid description\n");
		else if (max_activities(c))
			printf("too many activities\n");
		else {
			add_new_activity(des, activities, c);
		}
	}
}

void list_tasks_in_activity(char activity[], task tasks[], char activities[][ACT_LEN], counter c[]) {
	if (!is_activity(activity, activities, c))
		printf("no such activity\n");

	else {

	}
}

int main() {
	/* Initialize counters */
	task tasks[TASK];
	counter c = { 0, 0, 0, 0 };

	/* Declare command string */
	char cmd[CMD_LEN];
	char users[USER][USER_LEN];
	char activities[ACT][ACT_LEN];

	unsigned int dur;
	char des[TASK_LEN];
	char act[ACT_LEN];
	char user[USER_LEN];
	unsigned int ids[26];
	unsigned int size;
	unsigned int id;

	/* While user doesn't quit the program */
	for (get_cmd(cmd); get_cmd_name(cmd) != EXIT; get_cmd(cmd)) {
		get_args(cmd, &dur, des, act, user, ids, &size, &id);
		switch(get_cmd_name(cmd)) {
			case NEW_TASK:
				new_task(dur, des, &c, tasks);
				break;
			case LIST_TASK:
				list_tasks(cmd, ids, &size, tasks, &c);
				break;
			case FOWARD_TIME:
				foward_time(dur, &c);
				break;
			case ADD_USER:
				add_user(cmd, user, &c, users);
				break;
			case MOVE_TASK:
				move_task(id, user, act, tasks, users, &c, activities);
				break;
			case ADD_ACTIVITY:
				add_activity(cmd, des, activities, &c);

		}
	}

	return 0;
}
