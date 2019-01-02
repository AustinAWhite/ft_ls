#include "ft_ls.h"

static void	item_cpy(t_item **left, t_item *right)
{
	(*left)->name = right->name;
	(*left)->path = right->path;
	(*left)->date = right->date;
    (*left)->tv_nsec = right->tv_nsec;
	(*left)->st_mode = right->st_mode;
	(*left)->st_nlink = right->st_nlink;
	(*left)->st_uid = right->st_uid;
	(*left)->st_gid = right->st_gid;
	(*left)->st_size = right->st_size;
	(*left)->st_blocks = right->st_blocks;
}

void	ls_swap_item(t_item **left, t_item **right)
{
	t_item	tmp;

	tmp = **left;
	item_cpy(left, *right);
	item_cpy(right, &tmp);
}

static void        ls_reverse(t_item **files)
{
    t_item	*p;
	t_item	*q;
	t_item	*r;

	p = *files;
	q = NULL;
	while (p)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	*files = q;
}

static void        ls_lexi_sort(t_item **files)
{
    t_item *left;
    t_item *right;

    left = *files;
    while (left)
    {
        right = left->next;
        while (right)
        {
            if (ft_strcmp(left->name, right->name) > 0)
                ls_swap_item(&left, &right);
            right = right->next;
        }
        left = left->next;
    }
}

t_item      *ls_sort(t_item *files, t_flg flg)
{
    if (!files)
        return (NULL);
    ls_lexi_sort(&files);
    if (flg.t)
        ls_time_sort(&files);
    if (flg.r)
        ls_reverse(&files);
    return (files);
}