#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

/* Increments the counters by the specified increment */
void
increment_counter(unsigned inc, char type, data d[]) {
	switch (type) {
		/* Increment task index */
	case 't':
		TASK_INDEX += inc;
		break;
		/* Increment system time */
	case 'n':
		TIME += inc;
		break;
		/* Increment user index */
	case 'u':
		USER_INDEX += inc;
		break;
		/* Increment activity index */
	case 'a':
		ACTIVITY_INDEX += inc;
		break;
	}
}
