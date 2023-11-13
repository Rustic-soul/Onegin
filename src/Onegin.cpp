#include "../include/Onegin.h"

size_t search_size_file(FILE *fp_src, int* error_check)
{
    assert(fp_src != NULL);
    assert(error_check   != NULL);

	long start_ftell = ftell(fp_src);
    fseek(fp_src, 0, SEEK_END);
    size_t size_file = (size_t)ftell(fp_src);
    fseek(fp_src, start_ftell, SEEK_SET);

    assert(size_file > 0);
    printf(">>Size file: [%lu]\n", size_file);
    
	if (size_file <= 0)
	{
		fprintf(stderr, "ERROR: Unreal value\n");
		*error_check = ERROR_UNREAL_VALUE;
	}

    return size_file;
}

char* create_buf(FILE *fp_src, Data_t* text, int* error_check)
{
	assert(fp_src != NULL);
	assert(text != NULL);
	assert(text->size_file > 0);

	char* buf = (char *)calloc(text->size_file + 1, sizeof(char));
	if (buf == NULL)
	{
		fprintf(stderr, "ERROR: Pointer NULL\n");
		*error_check = ERROR_POINTER_NULL;
	}
	
	assert(buf != NULL);
	// printf(">>Buf create norm\n");

	size_t amount_char_file = fread(buf, sizeof(char), text->size_file, fp_src);
	if (amount_char_file != text->size_file)
	{
		fprintf(stderr, "ERROR: Unreal value\n");
		*error_check = ERROR_UNREAL_VALUE;
	}
	
	printf(">>Characters read: [%lu]\n", amount_char_file);
	assert(ferror(fp_src) == 0);

	if (ferror(fp_src) != 0)
	{
		fprintf(stderr, "ERROR: Read from file\n");
		*error_check = ERROR_READ_TEXT;
	}
	
	buf[text->size_file] = '\0';
	printf(">>Buffer is full\n");

	return buf;
}

Line* split_lines(char *buf, size_t sz_buf, size_t amount_lines, int* error_check)
{
    Line* lines = (Line *)calloc(amount_lines, sizeof(Line));
    assert(lines != NULL);

	lines[0].line = buf;
	
	short length_line = 0;
    for (size_t i = 0, j = 1; i < sz_buf; i++)
    {
		length_line++;

        if (buf[i] == '\n')
        {
            buf[i] = '\0'; 
            lines[j].line = &buf[i + 1];
            lines[j - 1].length_line = length_line;
			length_line = 0;
			j++;
        }
        else if (buf[i] == '\0')
		{
			lines[j - 1].length_line = length_line;
		}
		assert(j <= amount_lines);
		if (j > amount_lines)
		{
			fprintf(stderr, "ERROR: Output bordered massive\n");
			*error_check = ERROR_BORDER_MASSIVE;
		}
    }
    
	// printf(">>Completed create massive lines\n");

    return lines;
}

int compare(const void *arg1, const void *arg2)
{ 	
	assert(arg1 != NULL);
	assert(arg2 != NULL);
	
	const char *str1 = (*(const Line*)arg1).line;
	const char *str2 = (*(const Line*)arg2).line;
	
	assert(str1 != NULL);
	assert(str2 != NULL);
	
	int i = 0, j = 0;
	while (str1[i] != '\0' && str2[j] != '\0')
	{
		while ((isalpha(str1[i]) == 0) && (str1[i] !='\0'))
			i++;
		
		while ((isalpha(str2[j]) == 0) && (str2[j] != '\0'))
			j++;

		if ((str1[i] == str2[j]) && (str1[i] != '\0'))
		{
			i++;
			j++;
		}
		else
			break;
	}

	return  str1[i] - str2[j];
}

int compare_reverse(const void* arg1, const void* arg2)
{
	assert(arg1 != NULL);
	assert(arg2 != NULL);

	const char *str1 = (*(const Line*)arg1).line;
	const char *str2 = (*(const Line*)arg2).line;
	
	int i = (*(const Line*)arg1).length_line - 2;
	int j = (*(const Line*)arg2).length_line - 2; 

	while ((i >= 0) && (j >= 0) && (str1[i] != '\0') && (str2[j] != '\0'))
	{
		while ((isalpha(str1[i]) == 0) && (str1[i] !='\0'))
			i--;
		
		while ((isalpha(str2[j]) == 0) && (str2[j] != '\0'))
			j--;

		if ((str1[i] == str2[j]) && (str1[i] != '\0'))
		{
			i--;
			j--;
		}
		else
			break;
	}

	return str1[i] - str2[j];
}

int sorted_text(Data_t* text, int config, const char* pth)
{
	switch (config)
	{
	case NORMAL:
		qsort(text->lines, text->amount_lines, sizeof(Line), compare);
		break;
	case REVERSE:
		qsort(text->lines, text->amount_lines, sizeof(Line), compare_reverse);
		break;
	default:
		fprintf(stderr, "ERROR: Config is not from switch case\n");
		break;
	}
	
    FILE *fp_out = NULL;
	if ((fp_out = fopen(pth, "w")) == NULL)
	{
		fprintf(stderr, "ERR0R: Cannot open file\n");
		return ERROR_OPEN_FILE;
	}
	assert(fp_out != NULL);

    for (size_t i = 0; i < text->amount_lines; i++)
	{
        fprintf(fp_out, "%s\n", text->lines[i].line);
	}

	if (fclose(fp_out) != 0)
	{
		fprintf(stderr, "ERROR: Cannot close file\n");
		return ERROR_CLOSE_FILE;
	}

	return 0;
}

int determine_number_lines(char *buf, size_t sz_buf, size_t *n_lines)
{
	assert(buf != NULL);

    size_t amount_lines = 0;
	if (buf[sz_buf - 1] != '\0')
	{
		amount_lines++;
	}

    for (size_t i = 0; i < sz_buf; i++)
    {
        if (buf[i] == '\n')
            amount_lines++;
    }
    printf(">>Amount lines: [%lu]\n", amount_lines);

	if (amount_lines <= 0)
	{
		fprintf(stderr, "ERROR: Unreal value\n");
		return ERROR_UNREAL_VALUE;
	}

	*n_lines = amount_lines;
	
	return 0;
}