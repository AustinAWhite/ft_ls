#include "ft_ls.h"

static void		display_link_name(char *link_path)
{
	int		len;
	char	target_path[256];
	
	len = readlink(link_path, target_path, sizeof(target_path));
	target_path[len] = '\0';
    ft_putstr(" -> ");
    ft_putstr(target_path);
}

static void    display_date(time_t date)
{
        char    *str1;
        char    *str2;
        time_t  actualtime;

        actualtime = time(0);
        str1 = ctime(&date);
        if ((actualtime - 15778463) > date || actualtime < date)
        {
                str2 = ft_strnew(6);
                str2 = ft_strsub(str1, 20, 4);
                str1 = ft_strsub(str1, 4, 6);
                str1 = ft_strjoin(str1, "  ");
                str1 = ft_strjoin(str1, str2);
                free(str2);
        }
        else
                str1 = ft_strsub(str1, 4, 12);
        str1[12] = '\0';
        ft_putstr(str1);
        ft_putchar(' ');
        free(str1);
}

static void     ls_print_device_nums(char *path)
{
    struct stat fstat;

    lstat(path, &fstat);
    int min;
    int maj;

    min = (int)minor(fstat.st_rdev);
    maj = (int)major(fstat.st_rdev);
    putpad(4 - ft_strlen(ft_itoa(maj)));
    ft_putnbr(maj);
    ft_putchar(',');
    putpad(4 - ft_strlen(ft_itoa(min)));
    ft_putnbr(min);
    ft_putchar(' ');
}

static void    ls_long_file(t_flg flg, t_item *file, t_size size)
{
    ls_access(file->st_mode);
    print_int_formatted(file->st_nlink, size.links);
    if (getpwuid(file->st_uid))
        print_str_formatted(getpwuid(file->st_uid)->pw_name, size.users);
    else
        print_str_formatted(ft_itoa(file->st_uid), size.users);
    if (getgrgid(file->st_gid))
        print_str_formatted(getgrgid(file->st_gid)->gr_name, size.group);
    else
        print_str_formatted(ft_itoa(file->st_gid), size.group);
    if (S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode))
		ls_print_device_nums(file->path);
    else if (!(S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode)) && size.dev_in_list)
        print_int_formatted(file->st_size, size.size + 8);
    else
        print_int_formatted(file->st_size, size.size);
    display_date(file->date);
    ft_putstr(file->name);
    if (S_ISLNK(file->st_mode))
        display_link_name(file->path);
    ft_putchar('\n');
}

void	ls_print_long(t_flg flg, t_item *files, int isdir)
{
	t_item	*cur;
	t_size	size;
    int     test;
    int     listsize;

	cur = files;
	size = get_size(flg, files); 
    listsize = list_size(cur);
	if (isdir && (flg.a || (!flg.a && listsize > 2)))
	{
		ft_putstr("total ");
		ft_putnbr(size.total);
		ft_putchar('\n');
	}
	while (cur)
	{
		if (!(flg.a == 0 && cur->name[0] == '.'))
			ls_long_file(flg, cur, size);
		cur = cur->next;
	}
}