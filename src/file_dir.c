#include "../inc/myls.h"

static void ls_dir_subfile_iter(t_flg flg, t_item *dirs, int display_dir_name) {
	DIR		*iter;
	t_item	*files;
	int		putline;

	putline = 0;
	files = NULL;
	while (dirs) {
		iter = opendir(dirs->name);
		while (get_dir_subfile(&files, readdir(iter), 
						ft_strjoin(dirs->path, "/"))) {
			;
		}
		closedir(iter);
		if (files) {
			if (putline == 1) {
				ft_putchar('\n');
			}
			if (display_dir_name) {
				ft_putendl(ft_strjoin(dirs->name, ":"));
			}
			putline = 1;
			print_file(flg, files, 1);
		}
		files = NULL;
		dirs = dirs->next;
	}
}

void ls_dir(t_flg flg, t_list *path) {
	t_list	*cur;
	t_item	*dirs;

	cur = path;
	dirs = NULL;
	while (cur) {
		get_file(&dirs, cur->content, "");
		cur = cur->next;
	}
	dirs = ls_sort(dirs, flg);
	ls_dir_subfile_iter(flg, dirs, path->next != NULL);
}

void ls_file(t_flg flg, t_list *path) {
	t_list	*cur;
	t_item	*files;

	cur = path;
	files = NULL;
	flg.a = 1;
	while (cur) {
		get_file(&files, cur->content, "");
		cur = cur->next;
	}
	if (files) {
		print_file(flg, files, 0);
	}
}
