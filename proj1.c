# include <stdio.h>
# include <string.h>

/* Max value allowed */
# define TASK 10000
# define USER 50
# define ACT 10

/* Max structural values allowed */
# define CMD_LEN 100
# define TASK_LEN 50
# define ACT_LEN 20
# define USER_LEN 20

/* Define the key functions */
# define EXIT 'q'
# define NEW_TASK 't'
# define LIST_TASK 'l'
# define FOWARD_TIME 'n'
# define ADD_USER 'u'
# define MOVE_TASK 'm'
# define LIST_ACTIVITY_TASKS 'd'
# define ADD_ACTIVITY 'a'

/* Define task */
typedef struct {
	unsigned int id;
	char des[TASK_LEN];
	char user[USER_LEN];
	char act[ACT_LEN];
	unsigned int dur;
	unsigned int exec_time;
} task;

/* Define counter */
typedef struct {
	unsigned int task;
	unsigned int time;
	unsigned int user;
	unsigned int activity;
} counter;


/* Prompts the user for a command to
 * execute and saves it to a string */
void get_cmd(char cmd[]) {
	printf("? ");
	fgets(cmd, CMD_LEN, stdin);
}

/* Returns the key that matches the
 * command given by the user */
char get_key(char s[]) {
	return s[0];
}

/* Determines if a command has no arguments */
int is_no_arg_cmd(char cmd[]) {
	return (strlen(cmd) == 2);
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

/* Determines if a task id exists */
int is_task_id(unsigned int id, counter c[]) {
	return id >= 1 && id <= c[0].task + 1;
}

/* Determines if a task id exists */
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

int max_tasks(counter c[]) {
	return c[0].task == TASK;
}

void add_task_duration(unsigned int dur, unsigned int id, task tasks[]) {
	tasks[id-1].dur = dur;
}

void add_task_description(char des[], unsigned int id, task tasks[]) {
	strcpy(tasks[id-1].des, des);
}

void add_task_activity(char act[], unsigned int id, task tasks[]) {
	strcpy(tasks[id-1].act, act);
}

void get_new_id(unsigned int *id, counter c[]) {
	if (!max_tasks(c))
		*id = c[0].task + 1;
}

void increment_counter(counter c[], char type) {
	switch (type) {
		case 't':
			c[0].task += 1;
			break;
	}
}

/* Recieves string of numbers !
 * and returns size of array */
void get_ids(char cmd[], unsigned int ids[], unsigned int *size) {
	unsigned int i, number = 0;

	for (i = 0, *size = 0; cmd[i] != '\0'; i++) {
		if (cmd[i] >= '0' && cmd[i] <= '9')
			number = 10*number + (cmd[i] - '0');
		else if (cmd[i] == ' '){
			ids[*size] = number;
			*size += 1;
			number = 0;
		}
	}
	ids[*size] = number;
	*size += 1;
}

void get_args(char cmd[], unsigned int *dur, char des[], char act[], char user[], unsigned int ids[], unsigned int *size, unsigned int *id) {
	char ids_str[26];

	switch(get_key(cmd)) {
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

	else if (is_task(des, tasks, c))
		printf("duplicate description\n");

	else if (!is_valid_duration(dur))
		printf("invalid duration\n");

	/* Create the new task */
	else {
		add_task_duration(dur, id, tasks);
		add_task_description(des, id, tasks);
		add_task_activity("TO DO", id, tasks);

		increment_counter(c, 't');

		printf("task %u\n", c[0].task);
	}
}

void list_tasks(char cmd[], unsigned int ids[], unsigned int *size, task tasks[], counter c[]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < c[0].task; i++)
			printf("%u %s #%u %s\n", i+1, tasks[i].act, tasks[i].dur, tasks[i].des);

	else {
		for (i = 0; i < *size; i++)
			if (!is_task_id(ids[i], c))
				printf("%u no such task\n", ids[i]);

		for (i = 0; i < *size; i++)
			printf("%u %s #%u %s\n", ids[i], tasks[ids[i]-1].act, tasks[ids[i]-1].dur, tasks[ids[i]-1].des);
	}
}


void foward_time(unsigned int dur, counter c[]) {
	c[0].time += dur;

	printf("%u\n", c[0].time);
}


void add_user(char cmd[], char user[], counter c[], char users[][USER_LEN]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < c[0].user; i++)
			printf("%s\n", users[i]);

	else {
		strcpy(users[c[0].user], user);
		c[0].user += 1;
	}
}

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
		strcpy(activities[c[0].activity], des);
		c[0].activity += 1;
	}
}

void list_tasks_in_activity(char activity[], task tasks[], counter c[]);

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
	for (get_cmd(cmd); get_key(cmd) != EXIT; get_cmd(cmd)) {
		get_args(cmd, &dur, des, act, user, ids, &size, &id);
		switch(get_key(cmd)) {
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
