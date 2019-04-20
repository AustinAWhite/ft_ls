#include "../inc/myls.h"

static t_item *new_file(char *name, char *path) {
	t_item			*item;
	struct stat		fstat;

	lstat(path, &fstat);
	item = malloc(sizeof(t_item));
	item->name = ft_strdup(name);
	item->path = ft_strjoin(path, name);
	if (lstat(item->path, &fstat) == -1) {
		ls_error("ft_ls: ", item->name, 1);
		return (NULL);
	}
	item->tv_nsec = fstat.st_mtim.tv_nsec;
	item->st_mode = fstat.st_mode;
	item->st_nlink = fstat.st_nlink;
	item->st_uid = fstat.st_uid;
	item->st_gid = fstat.st_gid;
	item->st_size = fstat.st_size;
	item->st_blocks = fstat.st_blocks;
	item->date = fstat.st_mtime;
	item->next = NULL;
	return (item);
}

int get_dir_subfile(t_item **files, struct dirent *file, char *path) {
	t_item	*list;

	list = *files;
	if (!file)
		return (0);
	if (list) {
		while (list->next) {
			list = list->next;
		}
		list->next = new_file(file->d_name, path);
	} else {
		*files = new_file(file->d_name, path);
	}
	return (1);
}

void get_file(t_item **files, char *name, char *path) {
	t_item *list;

	list = *files;
	if (list) {
		while (list->next) {
			list = list->next;
		}
		list->next = new_file(name, path);
	} else {
		*files = new_file(name, path);
	}
}
