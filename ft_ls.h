#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <stdio.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# define SIX_MONTHS 15778463

typedef struct		s_flg
{
	unsigned int	l : 1;
	unsigned int	a : 1;
	unsigned int	r : 1;
	unsigned int	t : 1;
	unsigned int	rec : 1;    
}					t_flg;

typedef struct		s_item
{
	char			*name;
	char			*path;
	long			tv_nsec;
	time_t			date;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	quad_t			st_blocks;
	struct s_item	*next;
}					t_item;

typedef struct		s_fmt_width
{
	int				total;
	int				size;
	int				group;
	int				users;
	int				links;
	int				dev_in_list;
}					t_fmt_width;

void				ls_flg_error(char invalid);
void				ls_error(char *name, char *error, int ex);

void				ls_print_invalid(t_list *list);

int					isinstr(const char *s, int c);
int					list_size(t_item *files);
void				putpad(int n);
void				print_str_formatted(char *str, int maxsize);
void				print_int_formatted(int n, int maxsize);

void				ls_get_flg(int nb, char **av, t_flg *flg, t_list **path);
void				ft_ls(t_flg flg, t_list *path);
void				print_file(t_flg flg, t_item *files, int isdir);

void				ls_file(t_flg flg, t_list *path);
void				ls_dir(t_flg flg, t_list *path);

t_fmt_width			get_widths(t_flg flg, t_item *files);

int					get_dir_subfile(t_item **files, struct dirent *file, char *path);
void				get_file(t_item **files, char *name, char *path);

void				ls_print_basic(t_flg flg, t_item *files);
void				ls_print_long(t_flg flg, t_item *files, int isdir);
void				ls_access(mode_t mode);

void				ls_rec_flg(t_flg flg, t_item *files);

t_item				*ls_sort(t_item *files, t_flg flg);
void				ls_time_sort(t_item **files);
void				ls_swap_item(t_item **left, t_item **right);

#endif
