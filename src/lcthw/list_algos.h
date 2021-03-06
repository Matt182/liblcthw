#ifndef list_algos_h
#define list_algos_h

#include <lcthw/list.h>

typedef int (*List_compare) (const void *a, const void *b);

int List_bubble_sort(List *list, List_compare f);

List *List_merge_sort(List *list, List_compare f);

#endif
