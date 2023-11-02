#include "../include/main.h"

int create_buf(FILE *fp_src, Data_t* text)
{
	assert(fp_src != NULL);
	assert(text != NULL);
	assert(text->size_file > 0);

	text->buf = (char *)calloc(text->size_file + 1, sizeof(char));
	assert(text->buf != NULL);
	printf(">>Buf create norm\n");

	printf("Считали %lu\n", fread(text->buf, sizeof(char), text->size_file, fp_src));
	assert(ferror(fp_src) == 0);
	text->buf[text->size_file] = '\0';
	// printf(">>Buf заполнен\n");

	// for (int i = 293000; i < 293182; i++)
	//     printf("%c", buf[i]);

	// printf("::::last element buf: <%d>\n",    buf[size_file]);
	// printf("::::last element buf: <%d>\n",    buf[size_file - 1]);
	// printf("::::last -1 element buf: <%d>\n", buf[size_file - 2]);
	// printf("::::last -2 element buf: <%d>\n", buf[size_file - 3]);

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

    text->lines = (char **)calloc(amount_lines, sizeof(char *));
    assert(text->lines != NULL);

	text->lines[0] = text->buf;
    printf(">>Completed create massive lines\n");

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
    }

    return 0;
}

int compare(const void *arg1, const void *arg2)
{
	assert(arg1 != NULL);
	assert(arg2 != NULL);
	const char *str1 = *(const char **)arg1;
	const char *str2 = *(const char **)arg2;
	// printf("[[%s]]\n", str1);
	// printf("[[%s]]\n", str2);

	char ch1 = 'a';
	char ch2 = 'a';

	for (int i = 0, j = 0; ch1 != '\0' && ch2 != '\0';)
	{
		ch1 = *(str1 + i);
		ch2 = *(str2 + j);
		
		// fprintf(stdout, "[%c],<< %d >>\n", ch1, isalpha(ch1));
		while ((isalpha(ch1) == 0) && (ch1 !='\0'))
		{
			i++;
			ch1 = *(str1 + i);
		}
		
		// fprintf(stdout, "[%c],<< %d >>\n", ch2, isalpha(ch2));
		while ((isalpha(ch2) == 0) && (ch2 != '\0'))
		{
			j++;
			ch2 = *(str2 + j);
		}
		// fprintf(stdout, "ch1 {%c}{%d}\n", ch1, ch1);                        //    А - {53392}
																			//    Я - {53423}
		// fprintf(stdout, "ch2 {%c}{%d}\n", ch2, ch2);

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
	
	printf("[[%s]]\n", str1);
	printf("[[%s]]\n", str2);
	
	int length_str2 = 0;
	int length_str1 = 0; 
	for (int i = 0; *(str1 + i) != '\0'; i++)
		length_str1++;
	for (int i = 0; *(str2 + i) != '\0'; i++)
		length_str2++;
		
	printf("length1 < %d >\n", length_str1);
	printf("length2 < %d >\n", length_str2);

	char ch1 = 'a';
	char ch2 = 'a';

	for (int i = length_str1 - 1, j = length_str2 - 1; i >= 0 && j >= 0 && ch1 != '\0' && ch2 != '\0';)
	{
		ch1 = *(str1 + i);
		ch2 = *(str2 + j);
		
		fprintf(stdout, "[%c],<< %d >>\n", ch1, isalpha(ch1));
		while ((isalpha(ch1) == 0) && (ch1 !='\0'))
		{
			i--;
			ch1 = *(str1 + i);
		}
		
		fprintf(stdout, "[%c],<< %d >>\n", ch2, isalpha(ch2));
		while ((isalpha(ch2) == 0) && (ch2 != '\0'))
		{
			j--;
			ch2 = *(str2 + j);
		}
		fprintf(stdout, "ch1 {%c}{%d}\n", ch1, ch1);                        //    А - {53392}
																			//    Я - {53423}
		fprintf(stdout, "ch2 {%c}{%d}\n", ch2, ch2);
		
		if ((ch1 == ch2) && (ch1 != '\0'))
		{
			i--;
			j--;
			continue;
		}
		else
			break;
	}
	printf("{{%d}}\n", ch1 - ch2);
	return ch1 - ch2;
}

void my_print(char **lines, int num_str)
	{
	unsigned char** lines_u = (unsigned char**)lines;
	unsigned char symbol = 'a';
	for (int i = 0; symbol != '\n' && symbol != '\0'; i++)
	{
		symbol = *(*(lines_u + num_str - 1) + i);
		fprintf(stdout, "%c", symbol);
	}
	// symbol = 1;
	// for (int i = 0; symbol != '\n' && symbol != '\0'; i++)
	// {
	//     symbol = *(*(lines_u + num_str - 1) + i);
	//     fprintf(stdout, "%x ", (unsigned int)symbol);
	// }
	printf("\n");
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

    FILE *fp_out = fopen(pth, "w");
	assert(fp_out != NULL);

    for (size_t i = 0; i < text->amount_lines; i++)
        fprintf(fp_out, "%s\n", text->lines[i]);
    
	fclose(fp_out);
	return 0;
}