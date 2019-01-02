#include "ft_ls.h"

static void     ls_dir_aux(t_flg flg, t_item *dirlist, int display_dir_name)
{
    DIR     *iter;
    t_item  *files;
    int     putline;

    putline = 0;
    files = NULL;
    while (dirlist)
    {
        iter = opendir(dirlist->name);
        while (get_dir_subfile(&files, readdir(iter), 
                        ft_strjoin(dirlist->path, "/"), flg))
            ;
        closedir(iter);
        if (files)
        {
            if (putline == 1)
                ft_putchar('\n');
            if (display_dir_name)
                ft_putendl(ft_strjoin(dirlist->name, ":"));
            putline = 1;
            display_file(flg, files, 1);
        }
        files = NULL;
        dirlist = dirlist->next;
    }
}

void            ls_dir(t_flg flg, t_list *path)
{
    t_list	*cur;
	t_item	*dirlist;

	cur = path;
	dirlist = NULL;
	while (cur)
	{
		get_file(&dirlist, cur->content, "", flg);
		cur = cur->next;
	}
	dirlist = ls_sort(dirlist, flg);
	ls_dir_aux(flg, dirlist, path->next != NULL);
}

void            ls_file(t_flg flg, t_list *path)
{
    t_list	*cur;
	t_item	*files;

	cur = path;
	files = NULL;
	flg.a = 1;
	while (cur)
	{
		get_file(&files, cur->content, "", flg);
		cur = cur->next;
	}
	if (files)
		display_file(flg, files, 0);
}