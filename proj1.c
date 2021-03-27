# include <stdio.h>

# define MAX_CMD 100

/* Define the key functions */
# define EXIT 'q'
# define NEW_TASK 't'

/* Prompts the user for a command to
 * execute and saves it to a string */
void get_cmd(char cmd[]) {
    printf("? ");
    scanf("%s", cmd);
}

/* Returns the key that matches the
 * command given by the user */
char get_key(char s[]) {
    return s[0];
}

/* Adds a new task to the system,
 * printing the task id */
void new_task(int duration, char[]);

int main() {
    /* Declare command string */
    char cmd[MAX_CMD];

    /* While user doesn't quit the program */
    for (get_cmd(cmd); get_key(cmd) != EXIT; get_cmd(cmd))

        switch (get_key(cmd)) {
        }

    return 0;
}
