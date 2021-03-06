#include "../inc/myls.h"

static t_list *ls_invalid_sort(t_list *list) {
	t_list	*left;
	t_list	*right;
	char	*temp;

	left = list;
	while (left) {
		right = left->next;
		while (right) {
			if (ft_strcmp(left->content, right->content) > 0) {
				temp = left->content;
				left->content = right->content;
				right->content = temp;
			}
			right = right->next;
		}
		left = left->next;
	}
	return (list);
}

void ls_print_invalid(t_list *list) {
	t_list *cur; 

	cur = list;
	cur = ls_invalid_sort(cur);
	while (list) {
		ls_error("ft_ls: ", list->content, 0);
		list = list->next;
	}
}
