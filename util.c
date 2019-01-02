#include "ft_ls.h"

int             isinstr(const char *s, int c)
{
        int i;

        i = -1;
        while (s[++i])
                if (s[i] == c)
                        return (1);
        return (0);
}

int             list_size(t_item *files)
{
        int len;
        t_item *cur;

        len = 0;
        cur = files;
        while (cur)
        {
                len++;
                cur = cur->next; 
        }
        return (len);
}

void            putpad(int n)
{
        if (n < 0)
                return ;
        while (n != 0)
        {
                ft_putchar(' ');
                n--;
        }
}