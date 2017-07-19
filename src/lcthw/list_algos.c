#include <lcthw/dbg.h>
#include <lcthw/list_algos.h>
#include <lcthw/list.h>
#include <unistd.h>

void List_divide(List *list, List *list1, List *list2);
List *List_merge(List *list1, List *list2, List_compare f);

int List_bubble_sort(List *list, List_compare cmp_f)
{
	int count = List_count(list);
	if (count == 0 || count == 1) {
		return 0;
	}

	int sorted = 1;
	char *temp;
	do {
		sorted = 1;
		LIST_FOREACH(list, first, next, cur) {
			if (cur->next && cmp_f(cur->value, cur->next->value) > 0) {
				printf("in if\n");
				sorted = 0;

				temp = cur->value;
				cur->value = cur->next->value;
				cur->next->value = temp;
			}
		}
	} while (!sorted);

	return 0;
}

List *List_merge_sort(List *list, List_compare cmp_f)
{
	List * new_list = List_copy(list);

	int count = List_count(new_list);
	if (count == 0 || count == 1) return new_list;

	List *list1 = List_create();
	List *list2 = List_create();
	List_divide(new_list, list1, list2);
	List *list1d = List_merge_sort(list1, cmp_f);
	List *list2d = List_merge_sort(list2, cmp_f);
	List *res = List_merge(list1d, list2d, cmp_f);

	return res;
}

void List_divide(List *list, List *list1, List *list2)
{
	int orig_count = List_count(list);
	int left = (int)orig_count/2;
	int right = orig_count - left;

	list1->first = list->first;
	
	ListNode *cur = list->first;
	for (int i = 1; i < left; i++) {
		cur = cur->next;
	}
	list1->last = cur;
	list2->first = cur->next;
	cur->next = NULL;
	list->first->prev = NULL;
	cur = list2->first;
	for (int i = 1; i < right; i++) {
		cur = cur->next;
	}
	list2->last = cur;
}

List *List_merge(List *list1, List *list2, List_compare cmp_f)
{
	List *res = List_create();
	while (List_count(list1) > 0 || List_count(list2) > 0) {
		if (List_count(list1) == 0) {
			List_push(res, List_shift(list2));
		} else if (List_count(list2) == 0) {
			List_push(res, List_shift(list1));
		} else {
			if (cmp_f(list1->first->value, list2->first->value) > 0) {
				List_push(res, List_shift(list2));
			} else {
				List_push(res, List_shift(list1));
			}
		}
	}
	List_destroy(list1);
	List_destroy(list2);
	
	return res;
}
