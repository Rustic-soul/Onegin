#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void bubble_sort(void *base, size_t n_elem, size_t sz_elem, int (*compare)(const void *arg1, const void *arg2));
void swap(void *arg1, void* arg2, size_t sz_elem);

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
	for (size_t i = 0; i < ((sz_elem >> 3) & 0x7); i++)
	{
		uint64_t tmp[1] = {0};
		memcpy(tmp , arg1, sizeof(uint64_t));
		memcpy(arg1, arg2, sizeof(uint64_t));
		memcpy(arg2, tmp , sizeof(uint64_t));
		arg1 = (uint64_t*)arg1 + 1;
		arg2 = (uint64_t*)arg2 + 1;
	}
	if((sz_elem >> 2) & 0x1)
	{
		uint32_t tmp[1] = {};
		memcpy(tmp , arg1, sizeof(uint32_t));
		memcpy(arg1, arg2, sizeof(uint32_t));
		memcpy(arg2, tmp , sizeof(uint32_t));
		arg1 = (uint32_t*)arg1 + 1;
		arg2 = (uint32_t*)arg2 + 1;
	}
	if((sz_elem >> 1) & 0x1)
	{
		uint16_t tmp[1] = {};
		memcpy(tmp , arg1, sizeof(uint16_t));
		memcpy(arg1, arg2, sizeof(uint16_t));
		memcpy(arg2, tmp , sizeof(uint16_t));
		arg1 = (uint16_t*)arg1 + 1;
		arg2 = (uint16_t*)arg2 + 1;
	}
	if(sz_elem & 0x1)
	{
		uint8_t tmp[1] = {};
		memcpy(tmp , arg1, sizeof(uint8_t));
		memcpy(arg1, arg2, sizeof(uint8_t));
		memcpy(arg2, tmp , sizeof(uint8_t));
	}
}
