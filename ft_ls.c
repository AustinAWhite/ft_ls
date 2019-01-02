#include "ft_ls.h"

void	print_file(t_flg flg, t_item *files, int isdir)
{
	t_item	*cur;

	cur = files;
	cur = ls_sort(cur, flg);
	(flg.l == 1) ? ls_print_long(flg, cur, isdir) : ls_print_basic(flg, cur);
	if (flg.rec == 1)
		ls_rec_flg(flg, cur);
}

static int		handlelink(t_flg flg, t_list **cur, t_list **file)
{
	struct stat fstat;

	lstat((*cur)->content, &fstat);
	if (S_ISLNK(fstat.st_mode))
	{
		ft_lstappend(file, (*cur)->content, (*cur)->content_size);
		(*cur) = (*cur)->next;
		return (1);
	}
	return (0);
}

static void	ls_walk_paths(t_flg flg, t_list **path, 
							t_list **invalid, t_list **file, t_list **directory)
{
	t_list	*cur;
	DIR		*iter;

	cur = *path;
	while (cur)
	{
		if (handlelink(flg, &cur, file))
			continue;
		if ((iter = opendir(cur->content)) == NULL)
			errno != ENOTDIR ? 
				ft_lstappend(invalid, cur->content, cur->content_size) : 
				ft_lstappend(file, cur->content, cur->content_size);
		else
		{
			ft_lstappend(directory, cur->content, cur->content_size);
			closedir(iter);
		}
		cur = cur->next;
	}
}

void    ft_ls(t_flg flg, t_list *path)
{
	t_list	*file;
	t_list	*directory;
	t_list	*invalid;

	invalid = NULL;
	file = NULL;
	directory = NULL;
	ls_walk_paths(flg, &path, &invalid, &file, &directory);
	if (invalid)
		ls_print_invalid(invalid);
	if (file)
		ls_file(flg, file);
	if (file && directory)
		ft_putchar('\n');
	if (directory)
		ls_dir(flg, directory);
}