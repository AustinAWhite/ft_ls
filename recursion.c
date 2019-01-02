#include "ft_ls.h"

void	ls_recurse(t_flg flg, char *path)
{
	t_item	*files;
	DIR		*dir;

	files = NULL;
	ft_putchar('\n');
	ft_putstr(path);
	ft_putstr(":\n");
	if ((dir = opendir(path)) != NULL)
	{
		while (get_dir_subfile(&files, readdir(dir), ft_strjoin(path, "/"), flg))
			;
		closedir(dir);
		if (files)
			print_file(flg, files, 1);
		files = NULL;
	}
	else
		ls_error("ft_ls: ", path, 0);
}

void	ls_rec_flg(t_flg flg, t_item *files)
{
    t_item	*cur;

	cur = files;
	while (cur)
	{
		if (cur->name && cur->path && S_ISDIR(cur->st_mode) &&
				ft_strcmp(".", cur->name) && ft_strcmp("..", cur->name) &&
				!(flg.a == 0 && cur->name[0] == '.'))
			ls_recurse(flg, cur->path);
		cur = cur->next;
	}
}