/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_fileds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 12:49:08 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 12:49:13 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		*get_file_type(int st_mode)
{
	char	*mode;

	mode = (char *)ft_memalloc(2);
	if ((st_mode & S_IFMT) == S_IFDIR)
		mode[0] = 'd';
	else if ((st_mode & S_IFMT) == S_IFCHR)
		mode[0] = 'c';
	else if ((st_mode & S_IFMT) == S_IFBLK)
		mode[0] = 'b';
	else if ((st_mode & S_IFMT) == S_IFREG)
		mode[0] = '-';
	else if ((st_mode & S_IFMT) == S_IFLNK)
		mode[0] = 'l';
	else if ((st_mode & S_IFMT) == S_IFSOCK)
		mode[0] = 's';
	mode[1] = '\0';
	return (mode);
}

char		*get_permission(int st_mode)
{
	static const char	xtbl[10] = "rwxrwxrwx";
	char				*amode;
	int					i;
	int					j;

	amode = ft_strnew(9);
	i = -1;
	j = (1 << 8);
	while (++i < 9)
	{
		amode[i] = (st_mode & j) ? xtbl[i] : '-';
		j >>= 1;
	}
	if (st_mode & S_ISUID)
		amode[2] = 's';
	if (st_mode & S_ISGID)
		amode[5] = 's';
	if (st_mode & S_ISVTX)
		amode[8] = (st_mode & S_IXOTH) ? 't' : 'T';
	return (amode);
}

char		*get_date(struct stat statv)
{
	char	*date_f;
	char	*date;
	time_t	time_f;
	time_t	time_n;

	time_n = time(NULL);
	date = ft_strnew(12);
	ft_memcpy(&time_f, &statv.st_mtime, sizeof(statv.st_mtime));
	date_f = ctime(&time_f);
	if (time_n - time_f < 15778476 && time_f - time_n < 30)
		ft_memmove(date, (date_f + 4), 12);
	else
	{
		ft_memmove(date, (date_f + 4), 7);
		ft_memmove((date + 7), (date_f + 19), 5);
	}
	return (date);
}

char		*set_target(char *path_name)
{
	char *target_name;

	target_name = (char *)ft_memalloc(256);
	if (readlink(path_name, target_name, 256) != -1)
		return (target_name);
	ft_strdel(&target_name);
	return (NULL);
}

void		get_rdev_or_size(t_fileds_l *fileds_l, struct stat stat_f)
{
	if ((stat_f.st_mode & S_IFMT) == S_IFCHR
		|| (stat_f.st_mode & S_IFMT) == S_IFBLK)
	{
		fileds_l->major_st_rdev = ft_itoa(major(stat_f.st_rdev));
		fileds_l->minor_st_rdev = ft_itoa(minor(stat_f.st_rdev));
	}
	else
	{
		fileds_l->st_size = ft_itoa_off_t(stat_f.st_size);
	}
}
