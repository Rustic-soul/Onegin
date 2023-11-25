#include "../include/Onegin.h"
#include "../include/config.h"
#include <ctime>

int main()
{
	int ERROR_CHECK = 0;

	Data_t text1 = {};
	FILE *fp_src = fopen(FILE_NAME_SRC, "r");
	if (fp_src == NULL)
	{
		fprintf(stderr, "Error: File dont open\n");
		return ERROR_OPEN_FILE;
	}
	
	text1.size_file = search_size_file(fp_src, &ERROR_CHECK);
	if (ERROR_CHECK != 0)
		exit(ERROR_CHECK);

	text1.buf = create_buf(fp_src, &text1, &ERROR_CHECK);
	if  (ERROR_CHECK != 0)
	{
		fclose(fp_src);
		free(text1.buf);
		exit (ERROR_CHECK);
	}

	if ((ERROR_CHECK = determine_number_lines(text1.buf, text1.size_file, &text1.amount_lines)) != 0)
	{
		exit(ERROR_CHECK);
	}

	text1.lines = split_lines(text1.buf, text1.size_file, text1.amount_lines, &ERROR_CHECK);
	if (ERROR_CHECK != 0)
	{
		fclose(fp_src);
		free(text1.buf);
		free(text1.lines);
		exit(ERROR_CHECK);
	}
	
	if (sorted_text(&text1, NORMAL, FILE_NAME_OUT_1) != 0)
	{
		fclose(fp_src);
		free(text1.buf);
		free(text1.lines);
		exit(ERROR);
	}

	if (sorted_text(&text1, REVERSE, FILE_NAME_OUT_2) != 0)
	{
		fclose(fp_src);
		free(text1.buf);
		free(text1.lines);
		exit(ERROR);
	}

	fclose(fp_src);
	free(text1.buf);
	free(text1.lines);
	printf("TIME: %ld\n", clock());
}

