/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_main_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 14:04:30 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 14:04:40 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_main		*create_main_struct(void)
{
	t_main		*tmp;
	t_options	*options;

	tmp = ft_memalloc(sizeof(t_main));
	options = ft_memalloc(sizeof(t_options));
	tmp->total = 0;
	tmp->options = options;
	tmp->max_fileds = ft_memalloc(sizeof(t_max_fileds));
	return (tmp);
}

void		del_t_fileds_l_continue(t_fileds_l *fileds_l)
{
	if (fileds_l->major_st_rdev)
		ft_strdel(&fileds_l->major_st_rdev);
	if (fileds_l->minor_st_rdev)
		ft_strdel(&fileds_l->minor_st_rdev);
	if (fileds_l->st_size)
		ft_strdel(&fileds_l->st_size);
	if (fileds_l->date)
		ft_strdel(&fileds_l->date);
	if (fileds_l->d_name)
		ft_strdel(&fileds_l->d_name);
	if (fileds_l->ful_path)
		ft_strdel(&fileds_l->ful_path);
	if (fileds_l->target_name)
		ft_strdel(&fileds_l->target_name);
}

void		del_t_fileds_l(t_fileds_l *fileds_l)
{
	if (fileds_l)
	{
		if (fileds_l->file_type)
			ft_strdel(&fileds_l->file_type);
		if (fileds_l->permission)
			ft_strdel(&fileds_l->permission);
		if (fileds_l->st_nlink)
			ft_strdel(&fileds_l->st_nlink);
		if (fileds_l->author)
			ft_strdel(&fileds_l->author);
		if (fileds_l->group_name)
			ft_strdel(&fileds_l->group_name);
		del_t_fileds_l_continue(fileds_l);
		free(fileds_l);
	}
}

t_fileds_l	*get_stat_file(const char *path, struct dirent	*dp)
{
	t_fileds_l		*fileds_l;
	struct stat		stat_f;

	fileds_l = (t_fileds_l *)ft_memalloc(sizeof(t_fileds_l));
	if (lstat(path, &stat_f))
	{
		perror(path);
		return (NULL);
	}
	fileds_l->d_name = ft_strdup(dp->d_name);
	fileds_l->file_type = get_file_type(stat_f.st_mode);
	fileds_l->permission = get_permission(stat_f.st_mode);
	fileds_l->st_nlink = ft_itoa((int)stat_f.st_nlink);
	fileds_l->author = ft_strdup(getpwuid(stat_f.st_uid)->pw_name);
	get_rdev_or_size(fileds_l, stat_f);
	fileds_l->date = get_date(stat_f);
	fileds_l->st_blocks = stat_f.st_blocks;
	fileds_l->st_mtimespec = stat_f.st_mtimespec;
	if (fileds_l->file_type[0] == 'd')
		fileds_l->ful_path = ft_strdup(path);
	if ((stat_f.st_mode & S_IFMT) == S_IFLNK)
		fileds_l->target_name = set_target((char *)path);
	fileds_l->group_name = ft_strdup(getgrgid(stat_f.st_gid)->gr_name);
	return (fileds_l);
}

t_fileds_l	*get_stat_single_file(char *path, struct stat stat_f)
{
	t_fileds_l *fileds_l;

	fileds_l = (t_fileds_l *)ft_memalloc(sizeof(t_fileds_l));
	fileds_l->d_name = path;
	fileds_l->file_type = get_file_type(stat_f.st_mode);
	fileds_l->permission = get_permission(stat_f.st_mode);
	fileds_l->st_nlink = ft_itoa((int)stat_f.st_nlink);
	fileds_l->author = ft_strdup(getpwuid(stat_f.st_uid)->pw_name);
	get_rdev_or_size(fileds_l, stat_f);
	fileds_l->date = get_date(stat_f);
	fileds_l->st_blocks = stat_f.st_blocks;
	fileds_l->st_mtimespec = stat_f.st_mtimespec;
	if (fileds_l->file_type[0] == 'd')
		fileds_l->ful_path = ft_strdup(path);
	if ((stat_f.st_mode & S_IFMT) == S_IFLNK)
		fileds_l->target_name = set_target(path);
	fileds_l->group_name = ft_strdup(getgrgid(stat_f.st_gid)->gr_name);
	return (fileds_l);
}
