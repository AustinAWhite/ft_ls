#include "ft_ls.h"

static void     ls_set_flgs(t_flg *flg, char *str)
{
	int		i;

	i = 0;
	while (str[++i])
	{
		if (isinstr("lRart", str[i]) || (str[1] == '-' && !str[2]))
		{
            if (str[i] == 'l')
                flg->l = 1;
            if (str[i] == 'R')
                flg->rec = 1;
            if (str[i] == 'a')
                flg->a = 1;
            if (str[i] == 'r')
                flg->r = 1;
            if (str[i] == 't')
                flg->t = 1;   
		}
		else
			ls_flg_error(str[i]);
	}
}

void            ls_get_flg(int nb, char **av, t_flg *flg, t_list **path)
{
    int i;

	i = -1;
	while (++i < nb)
	{
        if (av[i + 1] && av[i + 1][0] == '-' && av[i + 1][1])
            ls_set_flgs(flg, av[i + 1]);
        else
            ft_lstappend(path, av[i + 1], ft_strlen(av[i + 1]));
	}
}