#include "ft_ls.h"

static void	copy_item(t_item **left, t_item *right)
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
	copy_item(left, *right);
	copy_item(right, &tmp);
}

static void        ls_reverse(t_item **files)
{
    t_item	*forward;
	t_item	*temp;
	t_item	*reverse;

	forward = *files;
	temp = NULL;
	while (forward)
	{
		reverse = temp;
		temp = forward;
		forward = forward->next;
		temp->next = reverse;
	}
	*files = temp;
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