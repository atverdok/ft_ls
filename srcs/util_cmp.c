/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 12:45:40 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 12:45:46 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	cmp_name(t_fileds_l *e1, t_fileds_l *e2, t_boolean r)
{
	if (e1 && e2)
	{
		if (r)
			return (ft_strcmp(e1->d_name, e2->d_name) <= 0);
		return (ft_strcmp(e1->d_name, e2->d_name) >= 0);
	}
	return (0);
}

int	cmp_date(t_fileds_l *e1, t_fileds_l *e2, t_boolean r)
{
	if (e1 && e2)
	{
		if (r)
		{
			if (e1->st_mtimespec.tv_sec == e2->st_mtimespec.tv_sec)
			{
				if (e1->st_mtimespec.tv_nsec == e2->st_mtimespec.tv_nsec)
					return (ft_strcmp(e1->d_name, e2->d_name) <= 0);
				return (e1->st_mtimespec.tv_nsec > e2->st_mtimespec.tv_nsec);
			}
			return (e1->st_mtimespec.tv_sec > e2->st_mtimespec.tv_sec);
		}
		if (e1->st_mtimespec.tv_sec == e2->st_mtimespec.tv_sec)
		{
			if (e1->st_mtimespec.tv_nsec == e2->st_mtimespec.tv_nsec)
				return (ft_strcmp(e1->d_name, e2->d_name) >= 0);
			return (e1->st_mtimespec.tv_nsec < e2->st_mtimespec.tv_nsec);
		}
		return (e1->st_mtimespec.tv_sec < e2->st_mtimespec.tv_sec);
	}
	return (0);
}
