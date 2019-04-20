#include "../inc/myls.h"

static int ls_timecmp(t_item *left, t_item *right) {
	if (left->date < right->date) {
		return (1);
	}
	if (left->date == right->date) {
		if (left->tv_nsec < right->tv_nsec) {
			return (1);
		}
	}
	return (0);
}

void ls_time_sort(t_item **files) {
	int i;
	int j;
	t_item *head;
	t_item *ptr;
	
	i = 0;
	j = list_size(*files);
	head = *files;
	ptr = *files;
	while (i++ < j) {
		while (ptr->next != NULL) {
			if ((ls_timecmp(ptr, ptr->next)) == 1) {
				ls_swap_item(&ptr, &ptr->next);
			}
			ptr = ptr->next;
		}
		ptr = head;
	}
}
