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

/* Tranforms command into its first argument */

/* Determines if a command has no arguments */
int is_no_arg_cmd(char cmd[]) {
	return (strlen(cmd) == 2);
}

int is_user(char user[], char users[][USER_LEN], counter c[]) {
	unsigned int i;

	for (i = 0; i < c[0].user; i++)
		if (!strcmp(users[i], user))
			return 1;

	return 0;
}

int is_activity(char act[], char activities[][ACT_LEN], counter c[]) {
	unsigned int i;

	for (i = 0; i < c[0].activity; i++)
		if (!strcmp(activities[i], act))
			return 1;

	return 0;
}

int is_task_id(unsigned int id, counter c[]) {
	return id <= c[0].task - 1;
}

int is_task(char des[], task tasks[], counter c[]) {
	unsigned int i;

	for (i = 0; i < c[0].task; i++)
		if (!strcmp(tasks[i].des, des))
			return 1;

	return 0;
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

void get_args(char cmd[]) {
	sscanf(cmd, "%*1c %[^\n]", cmd);
}

/* Adds a new task to the system,
 * printing the task id */
void new_task(char cmd[], counter c[], task tasks[]) {
	/* If task number limit is exceed */
	if (max_tasks(c))
		printf("too many tasks\n");

	else {
		get_args(cmd);
		sscanf(cmd, "%u %[^\n]", &tasks[c[0].task].dur, tasks[c[0].task].des);
		strcpy(tasks[c[0].task].act, "TO DO");
		c[0].task += 1;
		printf("task %u\n", c[0].task);
	}
}

void list_tasks(char cmd[], task tasks[], counter c[]) {
	unsigned int ids[26];
	unsigned int i, j, number = 0;

	/* Only l */
	if (is_no_arg_cmd(cmd))
		for (i = 0; i < c[0].task; i++)
			printf("%u %s #%u %s\n", i+1, tasks[i].act, tasks[i].dur, tasks[i].des);

	else {
		get_args(cmd);

		for (i = 0, j = 0; cmd[i] != '\0'; i++) {
			if (cmd[i] >= '0' && cmd[i] <= '9')
				number = 10*number + (cmd[i] - '0');
			else if (cmd[i] == ' '){
				ids[j++] = number;
				number = 0;
			}
		}
		ids[j++] = number;

		for (i = 0; i < j; i++)
			printf("%u %s #%u %s\n", ids[i], tasks[ids[i]-1].act, tasks[ids[i]-1].dur, tasks[ids[i]-1].des);
	}
}


void foward_time(char cmd[], counter c[]) {
	unsigned int dur;
	get_args(cmd);
	sscanf(cmd, "%u", &dur);
	c[0].time += dur;
	printf("%u\n", c[0].time);
}

void add_user(char cmd[], counter c[], char users[][USER_LEN]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < c[0].user; i++)
			printf("%s\n", users[i]);

	else {
		get_args(cmd);
		strcpy(users[c[0].user], cmd);
		c[0].user += 1;
	}
}

void move_task(char cmd[], char users[][USER_LEN], task tasks[], counter c[]) {
	unsigned int id;
	char user[USER_LEN], act[ACT_LEN];

	get_args(cmd);
	sscanf(cmd, "%u %[^ ] %[^\n]", &id, user, act);

	if (!is_user(user, users, c))
		printf("no such user\n");

	else {
		strcpy(tasks[id-1].user, user);
		strcpy(tasks[id-1].act, act);
	}
}


int main() {
	/* Declare command string */
	char cmd[CMD_LEN];
	char users[USER][USER_LEN];
	/*char activities[ACT][ACT_LEN];*/

	/* Initialize counters */
	task tasks[TASK];
	counter c = { 0, 0, 0, 0 };

	/* While user doesn't quit the program */
	for (get_cmd(cmd); get_key(cmd) != EXIT; get_cmd(cmd)) {
		switch(get_key(cmd)) {
			case NEW_TASK:
				new_task(cmd, &c, tasks);
				break;
			case LIST_TASK:
				list_tasks(cmd, tasks, &c);
				break;
			case FOWARD_TIME:
				foward_time(cmd, &c);
				break;
			case ADD_USER:
				add_user(cmd, &c, users);
				break;
			case MOVE_TASK:
				move_task(cmd, users, tasks, &c);
				break;
		}
	}

	return 0;
}
