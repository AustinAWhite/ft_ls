#include "ft_ls.h"

int main(int ac, char **av)
{
    t_flg flg;
    t_list *path;

    ft_bzero(&flg, sizeof(t_flg));
    path = NULL;
    if (ac > 1)
        ls_get_flg(ac - 1, av, &flg, &path);
    if (path == NULL)
        path = ft_lstnew(".", 1);
    ft_ls(flg, path);
    return (0);
}