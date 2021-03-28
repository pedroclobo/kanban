# include <stdio.h>

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

/* Define task */
typedef struct {
    unsigned int id;
    char *des;
    char *user;
    char *act;
    unsigned int dur;
    unsigned int exec_time;
} task;

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

/* Adds a new task to the system,
 * printing the task id */
void new_task(char cmd[], unsigned int *task_c, task tasks[]) {
    unsigned int dur;
    char des[100];

    sscanf(cmd, "f %u %[^\n]", &dur, des);

    tasks[*task_c].dur = dur;
    tasks[*task_c].des = des;
    *task_c += 1;

    printf("task %d\n", *task_c);
}

void list_tasks(int ids[]);

void foward_time(int dur);

void add_user(char user[]);

void move_taks(int id, char user[], char act[]);

int main() {
    /* Declare command string */
    char cmd[CMD_LEN];

    /* Tasks */
    task tasks[TASK];
    unsigned int task_c = 0;

    /* While user doesn't quit the program */
    for (get_cmd(cmd); get_key(cmd) != EXIT; get_cmd(cmd)) {
        switch(get_key(cmd)) {
            case NEW_TASK:
                new_task(cmd, &task_c, tasks);
        }
    }

    return 0;
}
