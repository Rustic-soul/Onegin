#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// const size_t n_elem = 10;

void bubble_sort(void *base, size_t n_elem, size_t sz_elem, int (*compare)(const void *arg1, const void *arg2));

void swap(void *arg1, void* arg2, size_t sz_elem);

// int compare(const void *arg1, const void *arg2);

// int compare2(const void *arg1, const void *arg2);

// int main()
// {

// 	int   nums[n_elem] = {};

// 	for (size_t i = 0; i < n_elem; i++)
// 		nums[i] = rand() % 1000;

// 	for (size_t i = 0; i < n_elem; i++)
// 		printf("[%3d]", nums[i]);
// 	printf("\n");

// 	bubble_sort(nums, n_elem, sizeof(int), compare);

// 	for (size_t i = 0; i < n_elem; i++)
// 		printf("[%3d]", nums[i]);
// 	printf("\n");

// 	char chars[n_elem] = {};

// 	for (size_t i = 0; i < n_elem; i++)
// 		chars[i] = (char)(74 - i);

// 	for (size_t i = 0; i < n_elem; i++)
// 		printf("[%c]", chars[i]);
// 	printf("\n");

// 	bubble_sort(chars, n_elem, sizeof(char), compare2);

// 	for (size_t i = 0; i < n_elem; i++)
// 		printf("[%c]", chars[i]);
// 	printf("\n");

// }

void bubble_sort(void *base, size_t n_elem, size_t sz_elem, int (*compare)(const void *arg1, const void *arg2))
{
	for (size_t i = 0, n_step = n_elem - 1; i < n_elem; i++)
	{
		for (size_t j = 0; j < n_step; j++)
			if (compare(((char*)base + j*sz_elem), ((char*)base + (j+1)*sz_elem)) > 0)
				swap(((char*)base + j*sz_elem), ((char*)base + (j+1)*sz_elem), sz_elem);
		n_step--;
	}
}

void swap(void *arg1, void* arg2, size_t sz_elem)
{
	size_t sz_type = sizeof(int64_t);

	while (sz_elem != 0)
	{
		size_t i = 0, j = sz_elem / sz_type;
		switch (sz_type)
		{
		case sizeof(int64_t):
			while (i < j)
			{
				int64_t tmp = *(int64_t*)arg1;
				*(int64_t*)arg1 = *(int64_t*)arg2;
				*(int64_t*)arg2 = tmp;
				arg1 = (int64_t*)arg1 + 1; 
				arg2 = (int64_t*)arg2 + 1;
				i++; 
			}
			break;		
	
		case sizeof(int32_t):
			while (i < j)
			{
				int32_t tmp = *(int32_t*)arg1;
				*(int32_t*)arg1 = *(int32_t*)arg2;
				*(int32_t*)arg2 = tmp;
				arg1 = (int32_t*)arg1 + 1; 
				arg2 = (int32_t*)arg2 + 1; 
				i++;
			}
			break;

		case sizeof(int16_t):
			while (i < j)
			{
				int16_t tmp = *(int16_t*)arg1;
				*(int16_t*)arg1 = *(int16_t*)arg2;
				*(int16_t*)arg2 = tmp;
				arg1 = (int16_t*)arg1 + 1; 
				arg2 = (int16_t*)arg2 + 1; 
				i++;
			}
			break;

		case sizeof(int8_t):
			while (i < j)
			{
				int8_t tmp = *(int8_t*)arg1;
				*(int8_t*)arg1 = *(int8_t*)arg2;
				*(int8_t*)arg2 = tmp;
				arg1 = (int8_t*)arg1 + 1; 
				arg2 = (int8_t*)arg2 + 1;
				i++; 
			}
			break;

		default:
			break;
		}

		sz_elem -= sz_type * j;
		sz_type /= 2;
	}
}

// int compare(const void *arg1, const void *arg2)
// {
// 	return *(const int*)arg1 - *(const int*)arg2; 
// }

// int compare2(const void *arg1, const void *arg2)
// {
// 	return *(const char*)arg1 - *(const char*)arg2; 
// }
