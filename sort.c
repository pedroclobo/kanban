#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

void
swap(task t1[], task t2[]) {
	task temp = t1[0];
	t1[0] = t2[0];
	t2[0] = temp;
}

int
less(task t1[], task t2[], char type) {
	if (type == 'a')
		return strcmp(t1[0].des, t2[0].des) < 0;
	else if (type == 'i')
		return t1[0].id < t2[0].id;
	else if (type == 'd') {
		if (t1[0].exec_time < t2[0].exec_time)
			return 1;
		else if (t1[0].exec_time == t2[0].exec_time)
			return strcmp(t1[0].des, t2[0].des) < 0;
		else
			return 0;
	}

	return -1;
}

int
partition(data d[], int l, int r, char type) {
	task v;

	int i = l - 1;
	int j = r;
	v = d[0].t[r];
	while (i < j) {
		while (less(&d[0].t[++i], &v, type));
		while (less(&v, &d[0].t[--j], type))
			if (j == 1)
				break;
		if (i < j)
			swap(&d[0].t[i], &d[0].t[j]);
	}
	swap(&d[0].t[i], &d[0].t[r]);
	return i;
}

void
quicksort(data d[], int l, int r, char type, char *order) {
	int i;

	if (r <= l)
		return;

	i = partition(d, l, r, type);
	quicksort(d, l, i - 1, type, order);
	quicksort(d, i + 1, r, type, order);
	*order = type;
}

void
bubble(data d[], int left, int right, char type, char *order) {
	int i, j;
	for (i = left; i < right; i++) {
		for (j = left; j < right + (left - i); j++)
			if (less(&d[0].t[j + 1], &d[0].t[j], type))
				swap(&d[0].t[j], &d[0].t[j + 1]);
	}
	*order = type;
}

void
insertion(data d[], int left, int right, char type, char *order) {
	task v;
	int i, j, loc;

	for (i = left + 1; i <= right; i++) {
		v = d[0].t[i];
		j = i - 1;

		loc = binarySearch(d, v, 0, j, type, order);

		while (j >= loc) {
			d[0].t[j + 1] = d[0].t[j];
			j--;
		}
		d[0].t[j + 1] = v;
	}
	*order = type;
}

int
binarySearch(data d[], task t, int low, int high, char type, char *order) {
	int mid;

	if (high <= low)
		return (less(&d[0].t[low], &t, type)) ? (low + 1) : low;

	mid = (low + high) / 2;

	if (less(&d[0].t[mid], &t, type))
		return binarySearch(d, t, mid + 1, high, type, order);
	return binarySearch(d, t, low, mid - 1, type, order);
}


void
merge(data d[], int l, int m, int r, char type) {
	task t[TASK];

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

void
mergesort(data d[], int l, int r, char type, char *order) {
	int m = (r + l) / 2;
	if (r <= l)
		return;
	mergesort(d, l, m, type, order);
	mergesort(d, m + 1, r, type, order);
	merge(d, l, m, r, type);
	*order = type;
}
