# include <stdio.h>
# include <string.h>

/* Max value allowed */
# define TASK 10000
# define USER 50

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

/* Define task */
typedef struct {
	unsigned int id;
	char des[TASK_LEN];
	char user[USER_LEN];
	char act[ACT_LEN];
	unsigned int dur;
	unsigned int exec_time;
} task;

/* Define user */
typedef struct {
	char user[USER_LEN];
} user;


/* Prompts the user for a command to
 * execute and saves it to a string */
void get_cmd(char cmd[]) {
	fgets(cmd, CMD_LEN, stdin);
}

/* Returns the key that matches the
 * command given by the user */
char get_key(char s[]) {
	return s[0];
}

/* Tranforms command into its first argument */
void get_args(char cmd[]) {
	sscanf(cmd, "%*2c %[^\n]", cmd);
}

/* Determines if a command has no arguments */
int is_no_arg_cmd(char cmd[]) {
	return (strlen(cmd) == 2);
}

/* Adds a new task to the system,
 * printing the task id */
void new_task(char cmd[], unsigned int *task_c, task tasks[]) {
	char act[ACT_LEN] = "TO DO";

	/* If task number limit is exceed */
	if (*task_c + 1 >= TASK)
		printf("too many tasks\n");

	/* Else */
	else {
		get_args(cmd);
		sscanf(cmd, "%u %[^\n]", &tasks[*task_c].dur, tasks[*task_c].des);
		sscanf(act, "%[^\n]", tasks[*task_c].act);
		*task_c += 1;
		printf("task %u\n", *task_c);
	}
}

void list_tasks(char cmd[], task tasks[], unsigned int *task_c) {
	unsigned int ids[26];
	unsigned int i, j, number = 0;

	/* Only l */
	if (is_no_arg_cmd(cmd))
		for (i = 0; i < *task_c; i++)
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


void foward_time(char cmd[], unsigned int *time) {
	unsigned int dur;
	get_args(cmd);
	sscanf(cmd, "%u", &dur);
	*time += dur;
	printf("%u\n", *time);
}

void add_user(char cmd[], unsigned int *user_c, user users[]) {
	unsigned int i;

	if (is_no_arg_cmd(cmd))
		for (i = 0; i < *user_c; i++)
			printf("%s\n", users[i].user);

	else {
		get_args(cmd);
		sscanf(cmd, "%[^\n]", users[*user_c].user);
		*user_c += 1;
	}
}

void move_taks(int id, char user[], char act[]);

int main() {
	/* Declare command string */
	char cmd[CMD_LEN];

	/* Tasks */
	task tasks[TASK];
	unsigned int task_c = 0;

	/* Time */
	unsigned int time = 0;

	/* Users */
	user users[USER];
	unsigned int user_c = 0;

	/* While user doesn't quit the program */
	for (get_cmd(cmd); get_key(cmd) != EXIT; get_cmd(cmd)) {
		switch(get_key(cmd)) {
			case NEW_TASK:
				new_task(cmd, &task_c, tasks);
				break;
			case LIST_TASK:
				list_tasks(cmd, tasks, &task_c);
				break;
			case FOWARD_TIME:
				foward_time(cmd, &time);
				break;
			case ADD_USER:
				add_user(cmd, &user_c, users);
		}
	}

	return 0;
}
