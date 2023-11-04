#include "../include/main.h"
#include "../include/config.h"

int main()
{
	Data_t text1 = {};
	FILE *fp_src = fopen(FILE_NAME_SRC, "r");
	if (fp_src == NULL)
	{
		fprintf(stderr, "Error: File dont open\n");
		return ERROR_OPEN_FILE;
	}

	if (search_size_file(fp_src, &text1) != 0)
		exit(ERROR);

	if (create_buf(fp_src, &text1) != 0)
	{
		fclose(fp_src);
		free(text1.buf);
		exit(ERROR);
	}

	if (split_lines(&text1) != 0)
	{
		fclose(fp_src);
		free(text1.buf);
		free(text1.lines);
		exit(ERROR);
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
}

