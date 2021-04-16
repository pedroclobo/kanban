/*
 * File: proj1.h
 * Author: Pedro Lobo
 * Description: Header file where all macros and structs are defined.
*/

#ifndef _PROJ1_
#define _PROJ1_

/* True and False */
#define FALSE 0
#define TRUE 1

/* Max value of objects allowed */
#define TASK_MAX 10000
#define USER_MAX 50
#define ACTIVITY_MAX 10

/* Max string lenght values allowed */
#define CMD_LEN 100
#define TASK_LEN 50
#define ACTIVITY_LEN 20
#define USER_LEN 20

/* Define the keys used for each command */
#define EXIT 'q'
#define NEW_TASK 't'
#define LIST_TASK 'l'
#define FOWARD_TIME 'n'
#define ADD_USER 'u'
#define MOVE_TASK 'm'
#define LIST_ACTIVITY_TASKS 'd'
#define ADD_ACTIVITY 'a'

/* Define the vector indexers, time and
 * the sorting order of the tasks vector */
#define TASK_INDEX d[0].c.task
#define USER_INDEX d[0].c.user
#define ACTIVITY_INDEX d[0].c.activity
#define TIME d[0].c.time
#define ORDER d[0].order

/* Print statements */
#define PRINT_TASK_ID(x) printf("task %u\n", x)
#define PRINT_TASK_INFO(a, b, c, d) printf("%u %s #%d %s\n", a, b, c, d)
#define PRINT_TASK_DURATION_SLACK(a, b) printf("duration=%u slack=%d\n", a, b)

/* Access object atributtes with the vector index */
#define TASK_ACTIVITY(x) d[0].t[x].activity.description
#define TASK_ID(x) d[0].t[x].id
#define TASK_START_TIME(x) d[0].t[x].start_time
#define TASK_DESCRIPTION(x) d[0].t[x].description
#define TASK_DURATION(x) d[0].t[x].duration
#define USER_NAME(x) d[0].u[x].name
#define ACTIVITY_DESCRIPTION(x) d[0].a[x].description

/* Errors */
#define ERROR_TOO_MANY_TASKS printf("too many tasks\n")
#define ERROR_DUPLICATE_DESCRIPTION printf("duplicate description\n")
#define ERROR_INVALID_DURATION printf("invalid duration\n")
#define ERROR_NO_SUCH_TASK(x) printf("%u: no such task\n", x)
#define ERROR_INVALID_TIME printf("invalid time\n")
#define ERROR_USER_ALREADY_EXISTS printf("user already exists\n")
#define ERROR_TOO_MANY_USERS printf("too many users\n")
#define ERROR_NO_SUCH_TASK_NO_ARG printf("no such task\n")
#define ERROR_TASK_ALREADY_STARTED printf("task already started\n")
#define ERROR_NO_SUCH_USER printf("no such user\n")
#define ERROR_NO_SUCH_ACTIVITY printf("no such activity\n")
#define ERROR_DUPLICATE_ACTIVITY printf("duplicate activity\n")
#define ERROR_INVALID_DESCRIPTION printf("invalid description\n")
#define ERROR_TOO_MANY_ACTIVITIES printf("too many activities\n")


/* A activity contains a description
 * (can't be an emtpy string, can have whitespaces, can't have lowercase caracters) */
typedef struct {
	char description[ACTIVITY_LEN + 1];
} activity;

/* Every user has a name
 * (can't be an emtpy string, can't have whitespaces) */
typedef struct {
	char name[USER_LEN + 1];
} user;

/* A task has an unique id,
 * has a positive duration in time,
 * contains a description (can't be an emtpy string, can have whitespaces),
 * can be assigned to a user,
 * can be assigned to a activity,
 * and has a start time (the instant it leaves the acvitity "TO DO") */
typedef struct {
	unsigned id;
	unsigned duration;
	char description[TASK_LEN + 1];
	user user;
	activity activity;
	unsigned start_time;
} task;

/* Structure that contains all vector indexers and the time counter */
typedef struct {
	unsigned task;
	unsigned user;
	unsigned activity;
	unsigned time;
} counter;

/* The data structure holds a vector of tasks, users and activities,
 * it also has a counter to more easily index these vectors
 * and a order caracters that tells the order by which the tasks are organized:
 * a --> Sort alphabetically, by description
 * i --> Sort in ascending order of ids
 * d --> Sort in ascending order of task start time,
 *   if 2 tasks have the same start time, sort alphabetically, by description */
typedef struct {
	task t[TASK_MAX];
	activity a[ACTIVITY_MAX];
	user u[USER_MAX];
	counter c;
	char order;
} data;


/* Functions */
/* stdin */
void get_full_cmd(char cmd[]);
char get_cmd(char cmd[]);
int is_no_arg_cmd(char cmd[]);
void get_ids(char cmd[], unsigned ids[], unsigned *size);
void get_args(char cmd[], unsigned *uint, char string1[], char string2[],
	      unsigned ids[]);

/* Time */
void init_time(data d[]);
int is_valid_time(int dur);

/* Counter */
void init_counters(data d[]);
void increment_counter(unsigned inc, char type, data d[]);

/* Task */
int is_valid_task_duration(int dur);
int is_valid_task_description(char des[]);
int max_tasks(data d[]);
unsigned get_new_id(data d[]);
int is_task_id(unsigned id, data d[]);
int is_task(char des[], data d[]);
unsigned create_task(data d[]);
unsigned get_task_id(task t);
task get_task(unsigned id, data d[]);
int get_task_duration(unsigned id, data d[]);
char *get_task_description(unsigned id, data d[]);
char *get_task_activity(unsigned id, data d[]);
unsigned get_task_exec_time(unsigned id, data d[]);
void set_task_duration(int dur, unsigned id, data d[]);
void set_task_description(char des[], unsigned id, data d[]);
void set_task_activity(char act[], unsigned id, data d[]);
void set_task_start_time(unsigned id, data d[]);
void list_all_tasks(data d[]);

/* User */
int is_valid_user_name(char user[]);
int is_user(char user[], data d[]);
int max_users(data d[]);
void add_new_user(char user[], data d[]);
char *get_user_name(user user[]);

/* Activity */
int is_valid_activity(char des[]);
int is_activity(char act[], data d[]);
int max_activities(data d[]);
void add_new_activity(char des[], data d[]);
void init_activities(data d[]);

/* Sort */
void change_order_char(data d[], char type);
int less(task t1[], task t2[], char type);
void merge(data d[], int l, int m, int r, char type);
void mergesort(data d[], int l, int r, char type);

#endif
