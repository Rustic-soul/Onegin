#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *merge_sort(void *arr, size_t sz_arr, size_t sz_el, int (*compare)(const void *, const void *));
void *merger(void *arr_ptr1, size_t sz_arr1, void *arr_ptr2, size_t sz_arr2, size_t sz_el, int (*compare)(const void *, const void *));

void *merge_sort(void *arr, size_t sz_arr, size_t sz_el, int (*compare)(const void *, const void *))
{
    char *start_ptr = (char*)arr;
    char *end_ptr   = (char*)arr + (sz_arr - 1) * sz_el;

    if (sz_arr > 1)
    {
        char *middle_ptr = (char*)arr + (sz_arr / 2) * sz_el; 
        void *sort_ptr1  = merge_sort(start_ptr,  (size_t)(middle_ptr - start_ptr) / sz_el, sz_el    , compare);
        void *sort_ptr2  = merge_sort(middle_ptr, ((size_t)(end_ptr - middle_ptr) / sz_el) + 1, sz_el, compare);

        return merger(sort_ptr1, (size_t)(middle_ptr - start_ptr) / sz_el,
                      sort_ptr2, ((size_t)(end_ptr - middle_ptr) / sz_el) + 1, sz_el, compare);
    }
    else
    {
        void *sort_ptr = calloc(2, sizeof(sz_el));
        memcpy(sort_ptr, start_ptr, sz_el);

        return sort_ptr;
    }
}

void *merger(void *arr_ptr1, size_t sz_arr1, void *arr_ptr2, size_t sz_arr2, size_t sz_el, int (*compare)(const void *, const void *))
{
    void *merge_arr = calloc(sz_arr1 + sz_arr2 + 1, sz_el);

    size_t i = 0, j = 0, k = 0;
    while ((i < sz_arr1) || (j < sz_arr2))
    {
        if (i >= sz_arr1)
        {
            memcpy((char*)merge_arr + k*sz_el, (char*)arr_ptr2 + j*sz_el, sz_el);
            k++;
            j++;
            continue;
        }
        else if (j >= sz_arr2)
        {
            memcpy((char*)merge_arr + k*sz_el, (char*)arr_ptr1 + i*sz_el, sz_el);
            k++;
            i++;
            continue;
        }
        
        if (compare((char*)arr_ptr1 + i*sz_el, (char*)arr_ptr2 + j*sz_el) > 0)
        {
            memcpy((char*)merge_arr + k*sz_el, (char*)arr_ptr2 + j*sz_el, sz_el);
            k++;
            j++;
        }
        else if (compare((char*)arr_ptr1 + i*sz_el, (char*)arr_ptr2 + j*sz_el) < 0)
        {
            memcpy((char*)merge_arr + k*sz_el, (char*)arr_ptr1 + i*sz_el, sz_el);
            k++;
            i++;
        }
        else
        {
            memcpy((char*)merge_arr + k*sz_el, (char*)arr_ptr2 + j*sz_el, sz_el);
            memcpy((char*)merge_arr + (k+1)*sz_el, (char*)arr_ptr1 + i*sz_el, sz_el);
            j++;
            i++;
            k += 2;
        }
    }

    free(arr_ptr1);
    free(arr_ptr2);

    return merge_arr;
}
