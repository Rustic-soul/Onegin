#include "../include/main.h"

size_t search_size_file(FILE *fp_src, Data_t* text, int* error_check)
{
    assert(fp_src != NULL);
    assert(text   != NULL);

    fseek(fp_src, 0, SEEK_END);
    size_t size_file = (size_t)ftell(fp_src);
    fseek(fp_src, 0, SEEK_SET);

    assert(size_file > 0);
    printf(">>Size file: [%lu]\n", size_file);
    
	if (size_file <= 0)
	{
		fprintf(stderr, "ERROR: Unreal value\n");
		*error_check = ERROR_UNREAL_VALUE;
	}

	text->size_file = size_file;
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

Line* split_lines(Data_t *text, int* error_check)
{
    assert(text != NULL);

    size_t amount_lines = 1;
    for (size_t i = 0; i < text->size_file; i++)
    {
        if (text->buf[i] == '\n')
            amount_lines++;

        if (text->buf[i] == '\0')
            break;
    }
    printf(">>Amount lines: [%lu]\n", amount_lines);

	if (amount_lines <= 0)
	{
		fprintf(stderr, "ERROR: Unreal value\n");
		*error_check = ERROR_UNREAL_VALUE;
	}
	text->amount_lines = amount_lines;

    Line* lines = (Line *)calloc(amount_lines, sizeof(Line));
    assert(lines != NULL);

	lines[0].line = text->buf;
	
	short length_line = 0;
    for (size_t i = 0, j = 1; i < text->size_file; i++)
    {
		length_line++;

        if (text->buf[i] == '\n')
        {
            text->buf[i]   = '\0'; 
            lines[j].line = (text->buf + i + 1);
            lines[j - 1].length_line = length_line;
			length_line = 0;
			j++;
        }
        else if (text->buf[i] == '\0')
		{
			lines[j - 1].length_line = length_line;
            break;
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

	char ch1 = 'a';
	char ch2 = 'a';

	for (int i = 0, j = 0; ch1 != '\0' && ch2 != '\0';)
	{
		ch1 = *(str1 + i);
		ch2 = *(str2 + j);

		while ((isalpha(ch1) == 0) && (ch1 !='\0'))
		{
			i++;
			ch1 = *(str1 + i);
		}
		
		while ((isalpha(ch2) == 0) && (ch2 != '\0'))
		{
			j++;
			ch2 = *(str2 + j);
		}

		if ((ch1 == ch2) && (ch1 != '\0'))
		{
			i++;
			j++;
			continue;
		}
		else
			break;
	}
	return ch1 - ch2;
}

int compare_reverse(const void* arg1, const void* arg2)
{
	assert(arg1 != NULL);
	assert(arg2 != NULL);

	const char *str1 = (*(const Line*)arg1).line;
	const char *str2 = (*(const Line*)arg2).line;
	
	int length_str1 = (*(const Line*)arg1).length_line - 1;
	int length_str2 = (*(const Line*)arg2).length_line - 1; 

	char ch1 = 'a';
	char ch2 = 'a';

	for (int i = length_str1 - 1, j = length_str2 - 1; i >= 0 && j >= 0 && ch1 != '\0' && ch2 != '\0';)
	{
		ch1 = *(str1 + i);
		ch2 = *(str2 + j);
		
		while ((isalpha(ch1) == 0) && (ch1 !='\0'))
		{
			i--;
			ch1 = *(str1 + i);
		}
		
		while ((isalpha(ch2) == 0) && (ch2 != '\0'))
		{
			j--;
			ch2 = *(str2 + j);
		}

		if ((ch1 == ch2) && (ch1 != '\0'))
		{
			i--;
			j--;
			continue;
		}
		else
			break;
	}

	return ch1 - ch2;
}

int sorted_text(Data_t* text, int config, const char* pth)
{
	switch (config)
	{
	case NORMAL:
		qsort(text->lines, text->amount_lines, sizeof(Line), (int(*) (const void *, const void *)) compare);
		break;
	case REVERSE:
		qsort(text->lines, text->amount_lines, sizeof(Line), compare_reverse);
		break;
	default:
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