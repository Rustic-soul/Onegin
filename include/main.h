#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <ctype.h>

enum CONFIG{
	NORMAL,
	REVERSE
};

enum ERROR{
	ERROR = 1,
	ERROR_OPEN_FILE,
	ERROR_POINTER_NULL,
	ERROR_READ_TEXT,
	ERROR_UNREAL_VALUE,
	ERROR_BORDER_MASSIVE,
	ERROR_CLOSE_FILE
};

typedef struct DATA_TEXT{
    size_t size_file;
    char   *buf;
    size_t amount_lines;
    char   **lines;
} Data_t;


int split_lines(Data_t *text);
int search_size_file(FILE *fp_src, Data_t* text);
int create_buf(FILE *fp_src, Data_t* text);
int compare(const void *arg1, const void *arg2);
int compare_reverse(const void* arg1, const void* arg2);
void my_print(char **lines, int num_str);
int sorted_text(Data_t* text, int config, const char* pth);

#endif
