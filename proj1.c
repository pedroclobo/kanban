# include <stdio.h>
# include <string.h>

# include "definitions.h"

/* Prompts the user for a command to
 * execute and saves it to a string */
void get_cmd(char cmd[]) {
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

/* Determines if the maximum number of tasks has been reached */
int max_tasks(data d[]) {
	return d[0].c.task == TASK;
}

/* Increments the counter */
void increment_counter(int inc, char type, data d[]) {
	switch (type) {
		case 't':
			d[0].c.task += inc;
			break;
		case 'n':
			d[0].c.time += inc;
			break;
		case 'u':
			d[0].c.user += inc;
			break;
		case 'a':
			d[0].c.activity += inc;
			break;
	}
}

/* Sugests a task id for a new task and increments the task counter */
unsigned int get_new_id(data d[]) {
	if (!max_tasks(d))
		return d[0].c.task + 1;
	return 0;
}

/* Determines if a user exists */
int is_user(char user[], data d[]) {
	unsigned int i;

	for (i = 0; i < d[0].c.user; i++)
		if (!strcmp(d[0].u[i].name, user))
			return 1;

	return 0;
}

/* Determines if a activity exists */
int is_activity(char act[], data d[]) {
	unsigned int i;

	for (i = 0; i < d[0].c.activity; i++)
		if (!strcmp(d[0].a[i].des, act))
			return 1;

	return 0;
}

/* Determines if a task exists, based on its id */
int is_task_id(unsigned int id, data d[]) {
	return 1 <= id && id <= d[0].c.task;
}

/* Determines if a task exists, based on its description */
int is_task(char des[], data d[]) {
	unsigned int i;

	for (i = 0; i < d[0].c.task; i++)
		if (!strcmp(d[0].t[i].des, des))
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

/* Determines if the input is a valid activity description */
int is_valid_activity(char des[]) {
	int i;

	for (i = 0; des[i] != '\0'; i++)
		if ('a' <= des[i] && des[i] <= 'z')
			return 0;

	return 1;
}

/* Determines if the maximum number of users has been reached */
int max_users(data d[]) {
	return d[0].c.user == USER;
}

/* Determines if the maximum number of activities has been reached */
int max_activities(data d[]) {
	return d[0].c.activity == ACT;
}

unsigned create_task(data d[]) {
	unsigned id;

	id = get_new_id(d);
	d[0].t[id-1].id = id;
	strcpy(d[0].t[id-1].act, "TO DO");
	increment_counter(1, 't', d);

	return id;
}

/* Gives the specified duration to the task with the given id */
void add_task_duration(unsigned int dur, unsigned int id, data d[]) {
	d[0].t[id-1].dur = dur;
}

/* Gives the specified description to the task with the given id */
void add_task_description(char des[], unsigned int id, data d[]) {
	strcpy(d[0].t[id-1].des, des);
}

/* Gives the specified activity to the task with the given id */
void add_task_activity(char act[], unsigned int id, data d[]) {
	strcpy(d[0].t[id-1].act, act);
}

/* Returns the duration of the given task */
unsigned int get_task_duration(unsigned int id, data d[]) {
	return d[0].t[id-1].dur;
}

/* Returns the description of the given task */
char* get_task_description(unsigned int id, data d[]) {
	return d[0].t[id-1].des;
}

/* Returns the activity of the given task */
char* get_task_activity(unsigned int id, data d[]) {
	return d[0].t[id-1].act;
}

unsigned int get_task_exec_time(unsigned int id, data d[]) {
	return d[0].t[id-1].exec_time;
}

/* Recieves a username and adds it to the system, if the maximum number
 * of users has not been reached */
void add_new_user(char user[], data d[]) {
	if (!max_users(d)) {
		strcpy(d[0].u[d[0].c.user].name, user);
		increment_counter(1, 'u', d);
	}
}

/* Recieves a activity and adds it to the system, if the maximum number
 * of activities has not been reached */
void add_new_activity(char des[], data d[]) {
	if (!max_activities(d)) {
		strcpy(d[0].a[d[0].c.activity].des, des);
		increment_counter(1, 'a', d);
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

void swap(task t1[], task t2[]) {
	task temp = t1[0];
	t1[0] = t2[0];
	t2[0] = temp;
}

void sort_abc(data d[], int l, int r) {
	int i, j;
	for (i = l; i < r; i++) {
		int min = i;
		for (j = i+1; j <= r; j++)
			if (strcmp(d[0].t[j].des, d[0].t[min].des) < 0)
				min = j;
		swap(&d[0].t[i], &d[0].t[min]);
	}
}

void merge(task t[], int l, int m, int r) {
	int i, j, k;
	task aux[TASK];

	for (i = m+1; i > l; i--)
		aux[i-1] = t[i-1];
	for (j = m; j < r; j++)
		aux[r+m-j] = t[j+1];
	for (k = l; k <= r; k++) {
		if (aux[j].exec_time < aux[i].exec_time)
			t[k] = aux[j--];
		else if (aux[j].exec_time == aux[i].exec_time && strcmp(aux[j].des, aux[i].des) < 0)
			t[k] = aux[j--];
		else
			t[k] = aux[i++];
	}
}

void mergesort(task t[], int l, int r) {
	int m = (r+l)/2;

	if (r <= l)
		return;

	mergesort(t, l, m);
	mergesort(t, m+1, r);
	merge(t, l, m, r);
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
			sscanf(cmd, "%*2c %u %[^ ] %[^\n]", id, user, act);
			break;
		case ADD_ACTIVITY:
			sscanf(cmd, "%*2c %[^\n]", des);
			break;
		case LIST_ACTIVITY_TASKS:
			sscanf(cmd, "%*2c %[^\n]", act);
			break;
	}
}

/* Adds a new task to the system,
 * printing the task id */
void new_task(unsigned int dur, char des[], data d[]) {
	unsigned int id;

	/* If task number limit is exceed */
	if (max_tasks(d))
		printf("too many tasks\n");

	/* If a task with the same description already exists */
	else if (is_task(des, d))
		printf("duplicate description\n");

	/* If the duration in not a postive integer */
	else if (!is_valid_duration(dur))
		printf("invalid duration\n");

	/* Create the new task */
	else {
		id = create_task(d);
		add_task_duration(dur, id, d);
		add_task_description(des, id, d);

		printf("task %u\n", id);
	}
}

/* Lists created tasks */
void list_tasks(char cmd[], unsigned int ids[], unsigned int *size, data d[]) {
	unsigned int i, id;

	int ERROR = NO;

	/* If no arguments are specified, list all tasks */
	if (is_no_arg_cmd(cmd)) {
		sort_abc(d, 0, d[0].c.task - 1);
		for (i = 0; i < d[0].c.task; i++) {
			printf("%u %s #%u %s\n", d[0].t[i].id, d[0].t[i].act, d[0].t[i].dur, d[0].t[i].des);
			/*
			id = d[0].t[i].id;
			printf("%u %s #%u %s\n",
					id, get_task_activity(id, d), get_task_duration(id, d), get_task_description(id, d));
				*/
		}
	}

	else {
		/* Task id validation */
		for (id = 1; id < *size+1; id++)
			if (!is_task_id(ids[id-1], d)) {
				printf("%u no such task\n", ids[id-1]);
				ERROR = YES;
			}

		/* If all ids are valid, list the tasks */
		if (ERROR == NO) {
			for (id = 1; id < *size+1; id++) {
				printf("%u %s #%u %s\n",
						id, get_task_activity(id, d), get_task_duration(id, d), get_task_description(id, d));
			}
		}
	}
}


/* Foward the system time and prints current time */
void foward_time(int dur, data d[]) {
	if (!is_valid_time(dur))
		printf("invalid time\n");

	else {
		increment_counter(dur, 'n', d);
		printf("%u\n", d[0].c.time);
	}
}


/* Adds a user or lists all users */
void add_user(char cmd[], char user[], data d[]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < d[0].c.user; i++)
			printf("%s\n", d[0].u[i].name);

	else {
		/* Errors */
		if (is_user(user, d))
			printf("user already exists\n");
		else if (max_users(d))
			printf("too many users\n");

		/* If there are no errors */
		else {
			if (is_no_arg_cmd(cmd))
				for (i = 0; i < d[0].c.user; i++)
					printf("%s\n", d[0].u[i].name);
			else
				add_new_user(user, d);
		}
	}
}

/* Moves task from one activity to another */
void move_task(unsigned int id, char user[], char activity[], data d[]) {
	unsigned i;

	if (!is_task_id(id, d))
		printf("no such task\n");

	else if (!strcmp(activity, "TO DO"))
		printf("task already started\n");

	else if (!is_user(user, d))
		printf("no such user\n");

	else if (!is_activity(activity, d))
		printf("no such activity\n");

	else {
		add_task_activity(activity, id, d);
		for (i = 0; i < d[0].c.task; i++)
			if (d[0].t[i].id == id)
				d[0].t[i].exec_time = d[0].c.time;
		if (!strcmp(activity, "DONE")) {
			printf("duration=%u slack=%d\n", get_task_duration(id, d), d[0].c.time - get_task_exec_time(id, d) - get_task_duration(id, d));
		}
	}
}

void add_activity(char cmd[], char des[], data d[]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < d[0].c.activity; i++)
			printf("%s\n", d[0].a[i].des);

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

void tasks_in_activity(char activity[], task t[TASK], unsigned *size, data d[]) {
	unsigned i;

	for (i = 0; i < d[0].c.task; i++)
		if (!strcmp(d[0].t[i].act, activity)) {
			t[*size] = d[0].t[i];
			*size += 1;
		}
}

void list_tasks_in_activity(char activity[], data d[]) {
	task t[TASK];
	unsigned i, size = 0;

	if (!is_activity(activity, d))
		printf("no such activity\n");

	else {
		tasks_in_activity(activity, t, &size, d);
		mergesort(t, 0, size-1);
		for (i = 0; i < size; i++)
			printf("%u %u %s\n", t[i].id, t[i].exec_time, t[i].des);
	}
}

int main() {
	/* Declare data sctructure */
	data d;

	/* Declare command string */
	char cmd[CMD_LEN];
	unsigned int dur;
	char des[TASK_LEN];
	char act[ACT_LEN];
	char user[USER_LEN];
	unsigned int ids[26];
	unsigned int size;
	unsigned int id;

	/* Init activities */
	strcpy(d.a[0].des, "TO DO");
	strcpy(d.a[1].des, "IN PROGRESS");
	strcpy(d.a[2].des, "DONE");

	/* Counter */
	d.c.task = 0;
	d.c.time = 0;
	d.c.user = 0;
	d.c.activity = 3;

	/* While user doesn't quit the program */
	for (get_cmd(cmd); get_cmd_name(cmd) != EXIT; get_cmd(cmd)) {
		get_args(cmd, &dur, des, act, user, ids, &size, &id);
		switch(get_cmd_name(cmd)) {
			case NEW_TASK:
				new_task(dur, des, &d);
				break;
			case LIST_TASK:
				list_tasks(cmd, ids, &size, &d);
				break;
			case FOWARD_TIME:
				foward_time(dur, &d);
				break;
			case ADD_USER:
				add_user(cmd, user, &d);
				break;
			case MOVE_TASK:
				move_task(id, user, act, &d);
				break;
			case ADD_ACTIVITY:
				add_activity(cmd, des, &d);
				break;
			case LIST_ACTIVITY_TASKS:
				list_tasks_in_activity(act, &d);
				break;
		}
	}

	return 0;
}
