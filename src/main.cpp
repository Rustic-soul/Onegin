#include "../include/main.h"
#include "../include/config.h"

int main()
{
	Data_t text1 = {};
	FILE *fp_src = fopen(FILE_NAME_SRC, "r");
	assert(fp_src != NULL);
	printf(">>Open file\n"); 

	search_size_file(fp_src, &text1);

	create_buf(fp_src, &text1);
	// printf(">>Created buf completed. Path = [%p]\n", text1.buf);

	fclose(fp_src);

	split_lines(&text1);

	sorted_text(&text1, NORMAL, FILE_NAME_OUT_1);
	sorted_text(&text1, REVERSE, FILE_NAME_OUT_1);

    free(text1.buf);
    free(text1.lines);
}

//пасхалка
