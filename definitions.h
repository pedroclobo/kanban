/* Yes and No */
# define NO 0
# define YES 1

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
	unsigned int task;
	unsigned int time;
	unsigned int user;
	unsigned int activity;
} counter;

/* Main structure */
typedef struct {
	user u[USER];
	activity a[ACT];
	task t[TASK];
	counter c;
} data;
