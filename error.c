#include "ft_ls.h"

void	error_flg(char invalid)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(invalid, 2);
	ft_putstr_fd("\nusage: ft_ls [-Ralrt] [file ...]\n", 2);
	exit(EXIT_FAILURE);
}

void	basicerror(char *name, char *error, int ex)
{
	ft_putstr_fd(name, 2);
	perror(error);
	if (ex)
		exit(EXIT_FAILURE);
}