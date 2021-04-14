#ifndef _DEFINITIONS_
#define _DEFINITIONS_

/* True and False */
#define FALSE 0
#define TRUE 1

/* Max value of objects allowed */
#define TASK 10000
#define USER 50
#define ACT 10

/* Max string lenght values allowed */
#define CMD_LEN 100
#define TASK_LEN 50
#define ACT_LEN 20
#define USER_LEN 20

/* Define the key functions */
#define EXIT 'q'
#define NEW_TASK 't'
#define LIST_TASK 'l'
#define FOWARD_TIME 'n'
#define ADD_USER 'u'
#define MOVE_TASK 'm'
#define LIST_ACTIVITY_TASKS 'd'
#define ADD_ACTIVITY 'a'

#define TASK_INDEX d[0].c.task
#define USER_INDEX d[0].c.user
#define ACTIVITY_INDEX d[0].c.activity
#define TIME d[0].c.time
#define ORDER d[0].order

/* Define task */
typedef struct {
	unsigned id;
	char des[TASK_LEN];
	char user[USER_LEN];
	char act[ACT_LEN];
	int dur;
	unsigned exec_time;
} task;

/* Define activity */
typedef struct {
	char des[ACT_LEN];
} activity;

/* Define user */
typedef struct {
	char name[USER_LEN];
} user;

/* Define counter */
typedef struct {
	unsigned task;
	unsigned time;
	unsigned user;
	unsigned activity;
} counter;

/* Main structure */
typedef struct {
	user u[USER];
	activity a[ACT];
	task t[TASK];
	counter c;
	char order;
} data;

/* Functions */
/* Command */
void get_full_cmd(char cmd[]);
char get_cmd(char cmd[]);
int is_no_arg_cmd(char cmd[]);

/* Counter */
void increment_counter(unsigned inc, char type, data d[]);

/* Task */
int max_tasks(data d[]);
unsigned get_new_id(data d[]);
int is_task_id(unsigned int id, data d[]);
int is_task(char des[], data d[]);
unsigned create_task(data d[]);
unsigned int get_task_id(task t);
task get_task(unsigned int id, data d[]);
int get_task_duration(unsigned id, data d[]);
char *get_task_description(unsigned id, data d[]);
char *get_task_activity(unsigned id, data d[]);
unsigned get_task_exec_time(unsigned id, data d[]);
void set_task_duration(int dur, unsigned int id, data d[]);
void set_task_description(char des[], unsigned int id, data d[]);
void set_task_activity(char act[], unsigned int id, data d[]);
void set_task_start_time(unsigned int id, data d[]);
void list_all_tasks(data d[]);

/* User */
int is_user(char user[], data d[]);
int max_users(data d[]);
void add_new_user(char user[], data d[]);
char *get_user_name(user user[]);

/* Activity */
int is_activity(char act[], data d[]);
int is_valid_activity(char des[]);
int max_activities(data d[]);
void add_new_activity(char des[], data d[]);

/* Sort */
void swap(task t1[], task t2[]);
int less(task t1[], task t2[], char type);
int equal(task t1[], task t2[], char type);
int partition(data d[], int l, int r, char type);
void quicksort(data d[], int l, int r, char type, char *order);
void bubble(data d[], int left, int right, char type, char *order);
void insertion(data d[], int left, int right, char type, char *order);
int binarySearch(data d[], task t, int low, int high, char type, char *order);
void insertionSort(data d[], int n, char type, char *order);
void merge(data d[], int l, int m, int r, char type);
void mergesort(data d[], int l, int r, char type, char *order);





#endif
