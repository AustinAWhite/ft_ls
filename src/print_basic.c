#include "../inc/myls.h"

void ls_print_basic(t_flg flg, t_item *files) {
	t_item	*cur;

	cur = files;
	while (cur) {
		if (!(flg.a == 0 && cur->name[0] == '.')) {
			ft_putendl(cur->name);
		}
		cur = cur->next;
	}
}
