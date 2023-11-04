#include "../include/main.h"

int create_buf(FILE *fp_src, Data_t* text)
{
	assert(fp_src != NULL);
	assert(text != NULL);
	assert(text->size_file > 0);

	text->buf = (char *)calloc(text->size_file + 1, sizeof(char));
	if (text->buf == NULL)
	{
		fprintf(stderr, "ERROR: Pointer NULL\n");
		return ERROR_POINTER_NULL;
	}
	
	assert(text->buf != NULL);
	printf(">>Buf create norm\n");

	size_t amount_char_file = fread(text->buf, sizeof(char), text->size_file, fp_src);
	
	printf(">>Считали [%lu] символов\n", amount_char_file);
	assert(ferror(fp_src) == 0);

	if (ferror(fp_src) != 0)
	{
		fprintf(stderr, "ERROR: Read from file\n");
		return ERROR_READ_TEXT;
	}
	
	text->buf[text->size_file] = '\0';
	printf(">>Buffer заполнен\n");

	return 0;
}

int search_size_file(FILE *fp_src, Data_t* text)
{
    assert(fp_src != NULL);
    assert(text   != NULL);

    fseek(fp_src, 0, SEEK_END);
    size_t size_file = (size_t)ftell(fp_src);
    fseek(fp_src, 0, SEEK_SET);

    assert(size_file > 0);
    printf(">>Search size file:: %lu\n", size_file);
    
	if (size_file <= 0)
	{
		fprintf(stderr, "ERROR: Unreal value\n");
		return ERROR_UNREAL_VALUE;
	}

	text->size_file = size_file;
    return 0;
}

int split_lines(Data_t *text)
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
    text->amount_lines = amount_lines;
    printf(">>Amount lines = %lu\n", amount_lines);

	if (text->amount_lines <= 0)
	{
		fprintf(stderr, "ERROR: Unreal value\n");
		return ERROR_UNREAL_VALUE;
	}

    text->lines = (char **)calloc(amount_lines, sizeof(char *));
    assert(text->lines != NULL);


	text->lines[0] = text->buf;

    for (size_t i = 0, j = 1; i < text->size_file; i++)
    {
        if (text->buf[i] == '\n')
        {
            text->buf[i]   = '\0'; 
            text->lines[j] = (text->buf + i + 1);
            j++;
        }
        else if (text->buf[i] == '\0')
            break;
		assert(j <= text->amount_lines);
		if (j > text->amount_lines)
		{
			fprintf(stderr, "ERROR: Output bordered massive\n");
			return ERROR_BORDER_MASSIVE;
		}
    }
    
	printf(">>Completed create massive lines\n");

    return 0;
}

int compare(const void *arg1, const void *arg2)
{
	assert(arg1 != NULL);
	assert(arg2 != NULL);

	const char *str1 = *(const char **)arg1;
	const char *str2 = *(const char **)arg2;

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

	const char *str1 = *((const char **)arg1);
	const char *str2 = *((const char **)arg2);
	
	int length_str2 = 0;
	int length_str1 = 0; 

	for (int i = 0; *(str1 + i) != '\0'; i++)
		length_str1++;
	for (int i = 0; *(str2 + i) != '\0'; i++)
		length_str2++;
		
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
		qsort(text->lines, text->amount_lines, sizeof(char *), compare);
		break;
	case REVERSE:
		qsort(text->lines, text->amount_lines, sizeof(char *), compare_reverse);
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
        fprintf(fp_out, "%s\n", text->lines[i]);
	}

	if (fclose(fp_out) != 0)
	{
		fprintf(stderr, "ERROR: Cannot close file\n");
		return ERROR_CLOSE_FILE;
	}

	return 0;
}