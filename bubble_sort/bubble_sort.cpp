#include <stdlib.h>
#include <stdio.h>

const int n_elem = 10;

void bubble_sort(void *base, size_t n_elem, size_t sz_elem, int (*compare)(const void *arg1, const void *arg2));

void swap(void *arg1, void* arg2, size_t sz_elem);

int compare(const void *arg1, const void *arg2);

int compare2(const void *arg1, const void *arg2);

int main()
{
	int   nums[n_elem] = {};

	for (int i = 0; i < n_elem; i++)
		nums[i] = rand() % 1000;

	for (int i = 0; i < n_elem; i++)
		printf("[%3d]", nums[i]);
	printf("\n");

	bubble_sort(nums, n_elem, sizeof(int), compare);

	for (int i = 0; i < n_elem; i++)
		printf("[%3d]", nums[i]);
	printf("\n");
	
	// char chars[n_elem] = {};

	// for (int i = 0; i < n_elem; i++)
	// 	chars[i] = 74 - i;

	// for (int i = 0; i < n_elem; i++)
	// 	printf("[%c]", chars[i]);
	// printf("\n");

	// bubble_sort(chars, n_elem, sizeof(char), compare2);

	// for (int i = 0; i < n_elem; i++)
	// 	printf("[%c]", chars[i]);
	// printf("\n");

}

void bubble_sort(void *base, size_t n_elem, size_t sz_elem, int (*compare)(const void *arg1, const void *arg2))
{
	for (int i = 0, n_step = n_elem - 1; i < n_elem; i++)
	{
		for (int j = 0; j < n_step; j++)
			if (compare((base + j*sz_elem), (base + (j+1)*sz_elem)) > 0)
				swap((base + j*sz_elem), (base + (j+1)*sz_elem), sz_elem);
		n_step--;
	}
}

void swap(void *arg1, void* arg2, size_t sz_elem)
{

	for (int i = 0; i < sz_elem; i++)
	{
		char tmp = ((char*)arg1)[i];
		((char*)arg1)[i] = ((char*)arg2)[i];
		((char*)arg2)[i] = tmp;
	}
}

int compare(const void *arg1, const void *arg2)
{
	return *(const int*)arg1 - *(const int*)arg2; 
}

int compare2(const void *arg1, const void *arg2)
{
	return *(const char*)arg1 - *(const char*)arg2; 
}
