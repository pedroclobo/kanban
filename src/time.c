/*
 * File: time.c
 * Author: Pedro Lobo
 * Description: File with all functions related to time.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj1.h"

/* Initialize time */
void
init_time(data d[]) {
	TIME = 0;
}

/* Time increments must be 0 or a positive integer */
int
is_valid_time(int dur) {
	return dur >= 0;
}
