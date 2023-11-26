#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

typedef struct {
	const char* line;
	int length_line;
} Line;

typedef struct {
    size_t size_file;
    char* buf;
    size_t amount_lines;
    Line* lines;
} Data_t;

enum CONFIG{
	NORMAL,
	REVERSE
};

enum ERROR{
	ERROR                = 1,
	ERROR_OPEN_FILE      = 2,
	ERROR_POINTER_NULL   = 3,
	ERROR_READ_TEXT      = 4,
	ERROR_UNREAL_VALUE   = 5,
	ERROR_BORDER_MASSIVE = 6,
	ERROR_CLOSE_FILE     = 7
};

size_t search_size_file(FILE *fp_src, int* error_check);

char* create_buf(FILE *fp_src, Data_t* text, int* error_check);

int determine_number_lines(char *buf, size_t sz_buf, size_t *n_lines);

Line* split_lines(char *buf, size_t sz_buf, size_t amount_lines, int* error_check);

int sorted_text(Data_t* text, int config, const char* pth);

int compare(const void *arg1, const void *arg2);

int compare_reverse(const void* arg1, const void* arg2);

// void bubble_sort(void *base, size_t n_elem, size_t sz_elem, int (*compare)(const void *arg1, const void *arg2));

void my_qsort(void* array, size_t sz_array, size_t sz_elem, int (*compare)(const void*, const void*));

void swap(void *arg1, void* arg2, size_t sz_elem);

#endif
