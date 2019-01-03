#include "ft_ls.h"

static void     get_grp_usr_width(t_fmt_width *widths, t_item *cur)
{
    int temp;

    if (getpwuid(cur->st_uid))
    {
        if ((temp = ft_strlen(getpwuid(cur->st_uid)->pw_name)) > widths->users)
            widths->users = temp;
    }
    else
    {
        if ((temp = (int)ft_strlen(ft_itoa(cur->st_uid)) > widths->users))
            widths->users = temp;
    }
    if (getgrgid(cur->st_gid))
    {
        if ((temp = ft_strlen(getgrgid(cur->st_gid)->gr_name)) > widths->group)
            widths->group = temp;
    }
    else
    {
        if ((temp = (int)ft_strlen(ft_itoa(cur->st_gid)) > widths->group))
            widths->group = temp;
    }
}

static void    get_max_values(t_fmt_width *widths, t_item *cur)
{
    int temp;

    widths->total += cur->st_blocks;
    get_grp_usr_width(widths, cur);
    if ((temp = ft_strlen(ft_itoa(cur->st_nlink))) > widths->links)
        widths->links = temp;
    if ((temp = ft_strlen(ft_itoa(cur->st_size))) > widths->size)
        widths->size = temp;
    if (S_ISCHR(cur->st_mode) || S_ISBLK(cur->st_mode))
        widths->dev_in_list = 1;
}

t_fmt_width  get_widths(t_flg flg, t_item *files)
{
    t_item	*cur;
	t_fmt_width	widths;

	ft_bzero(&widths, sizeof(t_fmt_width));
	cur = files;
	while (cur)
	{
		if (!(flg.a == 0 && cur->name[0] == '.'))
            get_max_values(&widths, cur);
		cur = cur->next;
	}
	return (widths);
}