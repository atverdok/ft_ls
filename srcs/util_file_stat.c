/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_file_stat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 12:47:55 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 12:48:00 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		get_make_stat(t_main *main_struct, t_node **head, char *ful_path,
		struct dirent *dp)
{
	t_fileds_l		*fileds_l;

	if ((fileds_l = get_stat_file(ful_path, dp)) != NULL)
	{
		if (main_struct->options && main_struct->options->t)
			sorted_insert(head, new_node(fileds_l),
					main_struct->options->r, cmp_date);
		else
			sorted_insert(head, new_node(fileds_l),
					main_struct->options->r, cmp_name);
	}
}

char		*make_full_path(const char *path, struct dirent	*dp)
{
	char	*ful_path;

	ful_path = ft_strnew(ft_strlen(path) + ft_strlen(dp->d_name) + 1);
	ft_strcpy(ful_path, path);
	if (ft_strcmp(ful_path, "/") != 0)
		ft_strcat(ful_path, "/");
	ft_strcat(ful_path, dp->d_name);
	return (ful_path);
}

t_node		*ft_list_dir(const char *path, t_main *main_struct)
{
	DIR				*dirp;
	char			*ful_path;
	t_node			*head;
	struct dirent	*dp;

	head = NULL;
	if ((dirp = opendir(path)) == NULL)
	{
		print_perror((void *)path);
		return (NULL);
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		ful_path = make_full_path(path, dp);
		if (main_struct->options && main_struct->options->a)
			get_make_stat(main_struct, &head, ful_path, dp);
		else
		{
			if (dp->d_name[0] != '.')
				get_make_stat(main_struct, &head, ful_path, dp);
		}
		ft_strdel(&ful_path);
	}
	(void)closedir(dirp);
	return (head);
}
