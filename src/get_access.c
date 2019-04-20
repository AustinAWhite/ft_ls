#include "../inc/myls.h"

static char get_type(mode_t mode) {
	if (S_ISLNK(mode))
		return ('l');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISFIFO(mode))
		return ('f');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('-');
}

void ls_access(mode_t mode) {
	char *acc;

	if ((acc = (char *)malloc(sizeof(char) * 11)) == NULL) {
		return ;
	}
	acc[0] = get_type(mode);
	(mode & S_IRUSR) ? (acc[1] = 'r') : (acc[1] = '-');
	(mode & S_IWUSR) ? (acc[2] = 'w') : (acc[2] = '-');
	(mode & S_IXUSR) ? (acc[3] = 'x') : (acc[3] = '-');
	(mode & S_IRGRP) ? (acc[4] = 'r') : (acc[4] = '-');
	(mode & S_IWGRP) ? (acc[5] = 'w') : (acc[5] = '-');
	(mode & S_IXGRP) ? (acc[6] = 'x') : (acc[6] = '-');
	(mode & S_IROTH) ? (acc[7] = 'r') : (acc[7] = '-');
	(mode & S_IWOTH) ? (acc[8] = 'w') : (acc[8] = '-');
	(mode & S_IXOTH) ? (acc[9] = 'x') : (acc[9] = '-');
	acc[10] = '\0';
	if (mode & S_ISUID)
		acc[3] = acc[3] == '-' ? 'S' : 's';
	if (mode & S_ISGID)
		acc[6] = acc[6] == '-' ? 'S' : 's';
	if (mode & S_ISVTX)
		acc[9] = acc[9] == '-' ? 'T' : 't'; 
	ft_putstr(acc);
	ft_putchar(' ');
	free(acc);
}
