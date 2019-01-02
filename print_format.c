#include "ft_ls.h"

void        print_int_formatted(int num, int maxsize)
{
    int		n;

	n = maxsize - ft_strlen(ft_itoa(num));
	while (n-- > 0)
		ft_putchar(' ');
	ft_putnbr(num);
	ft_putstr(" ");
}

void        print_str_formatted(char *str, int maxsize)
{
    int		n;

	n = maxsize - ft_strlen(str);
	ft_putstr(str);
	while (n-- > 0)
		ft_putchar(' ');
	ft_putstr("  ");
}