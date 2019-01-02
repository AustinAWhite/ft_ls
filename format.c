#include "ft_ls.h"

static void     get_grp_usr_size(t_size *size, t_item *cur)
{
    int temp;

    if (getpwuid(cur->st_uid))
    {
        if ((temp = ft_strlen(getpwuid(cur->st_uid)->pw_name)) > size->users)
            size->users = temp;
    }
    else
    {
        if ((temp = ft_strlen(ft_itoa(cur->st_uid)) > size->users))
            size->users = temp;
    }
    if (getgrgid(cur->st_gid))
    {
        if ((temp = ft_strlen(getgrgid(cur->st_gid)->gr_name)) > size->group)
            size->group = temp;
    }
    else
    {
        if ((temp = ft_strlen(ft_itoa(cur->st_gid)) > size->group))
            size->group = temp;
    }
}

static void    get_max_values(t_size *size, t_item *cur)
{
    int temp;

    size->total += cur->st_blocks;
    get_grp_usr_size(size, cur);
    if ((temp = ft_strlen(ft_itoa(cur->st_nlink))) > size->links)
        size->links = temp;
    if ((temp = ft_strlen(ft_itoa(cur->st_size))) > size->size)
        size->size = temp;
    if (S_ISCHR(cur->st_mode) || S_ISBLK(cur->st_mode))
        size->dev_in_list = 1;
}

t_size  get_size(t_flg flg, t_item *files)
{
    t_item	*cur;
	t_size	size;

	ft_bzero(&size, sizeof(t_size));
	cur = files;
	while (cur)
	{
		if (!(flg.a == 0 && cur->name[0] == '.'))
            get_max_values(&size, cur);
		cur = cur->next;
	}
	return (size);
}