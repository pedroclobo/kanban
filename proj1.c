# include <stdio.h>
# include <string.h>

# include "definitions.h"

/* Prompts the user for a command to execute and saves it the string cmd */
void get_full_cmd(char cmd[]) {
	fgets(cmd, CMD_LEN, stdin);
}

/* Returns the character that represents the command read from standart input */
char get_cmd(char cmd[]) {
	return cmd[0];
}

/* Determines if the given command has no arguments */
int is_no_arg_cmd(char cmd[]) {
	int i;

	/* A command string can contain spaces, tabs and newline chars */
	for (i = 1; cmd[i] != '\0'; i++)
		if (cmd[i] != ' ' && cmd[i] != '\n' && cmd[i] != '\t')
			return 0;

	return 'a' <= cmd[0] && cmd[0] <= 'z';
}

/* Determines if the maximum number of tasks has been reached */
int max_tasks(data d[]) {
	return d[0].c.task == TASK;
}

/* Increments the counters by the specified increment */
void increment_counter(int inc, char type, data d[]) {
	switch (type) {
		/* Increment task index */
		case 't':
			d[0].c.task += inc;
			break;
		/* Increment system time */
		case 'n':
			d[0].c.time += inc;
			break;
		/* Increment user index */
		case 'u':
			d[0].c.user += inc;
			break;
		/* Increment activity index */
		case 'a':
			d[0].c.activity += inc;
			break;
	}
}

/************/
/* Returns a id for a new task and increments the task index */
unsigned int get_new_id(data d[]) {
	if (max_tasks(d))
		return -1;

	increment_counter(1, 't', d);
	return d[0].c.task;
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
/* Task ids are between 1 and the current number of tasks */
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
		/* Activity description should not contain lowercase letters */
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

/* Creates a new task, returning the id of the new task */
unsigned create_task(data d[]) {
	unsigned id;

	id = get_new_id(d);
	d[0].t[id-1].id = id;
	strcpy(d[0].t[id-1].act, "TO DO");

	return id;
}

/* Returns the id of the given task */
unsigned int get_task_id(task t) {
	return t.id;
}

task get_task(unsigned int id, data d[]) {
	unsigned i;

	for (i = 0; i < d[0].c.task; i++)
		if (get_task_id(d[0].t[i]) == id)
			return d[0].t[i];

	/***********/
	return d[0].t[0];
}

/* Returns the duration of the given task */
unsigned get_task_duration(task t[]) {
	return t[0].dur;
}

/* Returns the description of the given task */
char* get_task_description(task t[]) {
	return t[0].des;
}

/* Returns the activity of the given task */
char* get_task_activity(task t[]) {
	return t[0].act;
}

/* Returns the instant the task as been started */
unsigned get_task_exec_time(task t[]) {
	return t[0].exec_time;
}

/* Gives the specified duration to the task with the given id */
void set_task_duration(unsigned int dur, unsigned int id, data d[]) {
	unsigned i;

	for (i = 0; i < d[0].c.task; i++)
		if (get_task_id(d[0].t[i]) == id)
			d[0].t[i].dur = dur;
}

/* Gives the specified description to the task with the given id */
void set_task_description(char des[], unsigned int id, data d[]) {
	unsigned i;

	for (i = 0; i < d[0].c.task; i++)
		if (get_task_id(d[0].t[i]) == id)
			strcpy(d[0].t[id-1].des, des);
}

/* Gives the specified activity to the task with the given id */
void set_task_activity(char act[], unsigned int id, data d[]) {
	unsigned i;

	for (i = 0; i < d[0].c.task; i++)
		if (get_task_id(d[0].t[i]) == id)
			strcpy(d[0].t[id-1].act, act);
}

void set_task_start_time(unsigned int id, data d[]) {
	unsigned i;

	for (i = 0; i < d[0].c.task; i++)
		if (get_task_id(d[0].t[i]) == id)
			d[0].t[i].exec_time = d[0].c.time;
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

	switch(get_cmd(cmd)) {
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
		set_task_duration(dur, id, d);
		set_task_description(des, id, d);

		printf("task %u\n", id);
	}
}

/* Lists created tasks */
void list_tasks(char cmd[], unsigned int ids[], unsigned int *size, data d[]) {
	unsigned int i;
	task t;

	/* If command is passed with no arguments */
	if (is_no_arg_cmd(cmd)) {

		/* Order all tasks alfabeticaly */
		sort_abc(d, 0, d[0].c.task - 1);

		/* List all tasks */
		for (i = 0; i < d[0].c.task; i++) {
			t = get_task(i+1, d);
			printf("%u %s #%u %s\n", d[0].t[i].id, d[0].t[i].act, d[0].t[i].dur, d[0].t[i].des);
		}
		return;
	}

	/* If command is passed with arguments */
	for (i = 0; i < *size; i++)

		/* If the id doesn't exist */
		if (!is_task_id(ids[i], d))
			printf("%u no such task\n", ids[i]);

		/* List task */
		else {
			t = get_task(i+1, d);
			printf("%u %s #%u %s\n", i+1, get_task_activity(&t), get_task_duration(&t), get_task_description(&t));
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


char* get_user_name(user user[]) {
	return user[0].name;
}

/* Adds a user or lists all users */
void add_user(char cmd[], char user[], data d[]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < d[0].c.user; i++)
			printf("%s\n", get_user_name(&d[0].u[i]));

	/* Error handling */
	else if (is_user(user, d))
		printf("user already exists\n");

	else if (max_users(d))
		printf("too many users\n");

	/* Add new user */
	else add_new_user(user, d);
}

/* Moves task from one activity to another */
void move_task(unsigned int id, char user[], char activity[], data d[]) {
	task t;

	if (!is_task_id(id, d))
		printf("no such task\n");

	else if (!strcmp(activity, "TO DO"))
		printf("task already started\n");

	else if (!is_user(user, d))
		printf("no such user\n");

	else if (!is_activity(activity, d))
		printf("no such activity\n");

	else {

		/* Set start_time if activity is "TO DO" */
		t = get_task(id, d);
		if (!strcmp(get_task_activity(&t), "TO DO"))
			set_task_start_time(id, d);

		/* Move task to activity */
		set_task_activity(activity, id, d);

		/* If task to move to is "DONE" */
		if (!strcmp(activity, "DONE")) {
			t = get_task(id, d);
			printf("duration=%u slack=%d\n", d[0].c.time - get_task_exec_time(&t), d[0].c.time - get_task_exec_time(&t) - get_task_duration(&t));
		}
	}
}

void get_tasks_in_activity(char activity[], task t[TASK], unsigned *size, data d[]) {
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
		get_tasks_in_activity(activity, t, &size, d);
		mergesort(t, 0, size-1);
		for (i = 0; i < size; i++)
			printf("%u %u %s\n", t[i].id, t[i].exec_time, t[i].des);
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
	for (get_full_cmd(cmd); get_cmd(cmd) != EXIT; get_full_cmd(cmd)) {
		get_args(cmd, &dur, des, act, user, ids, &size, &id);
		switch(get_cmd(cmd)) {
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
