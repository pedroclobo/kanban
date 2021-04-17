/*
 * File: sort.c
 * Author: Pedro Lobo
 * Description: Contains sort related functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj1.h"

/* Changes the order variable, that indicates the order by which the tasks are sorted
 * a --> Sort alphabetically, by description
 * i --> Sort in ascending order of ids
 * d --> Sort in ascending order of task start time,
 *   if 2 tasks have the same start time, sort alphabetically, by description */
void
change_order_char(data d[], char type) {
	ORDER = type;
}

/* Tells if t1 is less than t2, acording to the type caracter
 * a --> Sort alphabetically, by description
 * i --> Sort in ascending order of ids
 * d --> Sort in ascending order of task start time,
 *   if 2 tasks have the same start time, sort alphabetically, by description */
int
less(task t1[], task t2[], char type) {
	if (type == 'a')
		return strcmp(t1[0].description, t2[0].description) < 0;

	else if (type == 'i')
		return t1[0].id < t2[0].id;

	else if (type == 'd') {
		if (t1[0].start_time < t2[0].start_time)
			return TRUE;
		else if (t1[0].start_time == t2[0].start_time)
			return strcmp(t1[0].description, t2[0].description) < 0;
		else
			return FALSE;
	}
	return EXIT_FAILURE;
}

/* Implementation of merge sort to order a vector of tasks */
void
merge(data d[], int l, int m, int r, char type) {
	task t[TASK_MAX];

	int i, j, k;
	for (i = m + 1; i > l; i--)
		t[i - 1] = d[0].t[i - 1];

	for (j = m; j < r; j++)
		t[r + m - j] = d[0].t[j + 1];

	for (k = l; k <= r; k++)
		if (less(&t[j], &t[i], type))
			d[0].t[k] = t[j--];
		else
			d[0].t[k] = t[i++];
}

/* Merge sort algorithm */
void
mergesort(data d[], int l, int r, char type) {
	int m = (r + l) / 2;
	if (r <= l)
		return;
	mergesort(d, l, m, type);
	mergesort(d, m + 1, r, type);
	merge(d, l, m, r, type);

	/* Declare by wich criteria tasks have been sorted */
	change_order_char(d, type);
}
