/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_print_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 14:31:46 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 14:36:57 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	check_max_size_continue(t_main *main_struct, t_node *node)
{
	if (ft_strlen(node->fileds_l->date)
			> main_struct->max_fileds->max_time)
		main_struct->max_fileds->max_time = ft_strlen(
				node->fileds_l->date);
	if (ft_strlen(node->fileds_l->group_name) >
			main_struct->max_fileds->max_group)
		main_struct->max_fileds->max_group = ft_strlen(
				node->fileds_l->group_name);
	if (node->fileds_l->minor_st_rdev &&
			ft_strlen(node->fileds_l->minor_st_rdev) >
			main_struct->max_fileds->max_minor)
		main_struct->max_fileds->max_minor = ft_strlen(
				node->fileds_l->minor_st_rdev);
	if (node->fileds_l->major_st_rdev &&
			ft_strlen(node->fileds_l->major_st_rdev) >
			main_struct->max_fileds->max_major)
		main_struct->max_fileds->max_major = ft_strlen(
				node->fileds_l->major_st_rdev);
}

void	check_max_size_and_size(t_main *main_struct)
{
	t_node	*node;

	node = main_struct->head;
	while (node)
	{
		if (node->fileds_l)
		{
			main_struct->total += node->fileds_l->st_blocks;
			if (node->fileds_l->st_nlink && ft_strlen(node->fileds_l->st_nlink)
					> main_struct->max_fileds->max_nlink)
				main_struct->max_fileds->max_nlink = ft_strlen(
						node->fileds_l->st_nlink);
			if (node->fileds_l->st_size &&
					ft_strlen(node->fileds_l->st_size)
					> main_struct->max_fileds->max_size)
				main_struct->max_fileds->max_size = ft_strlen(
						node->fileds_l->st_size);
			if (ft_strlen(node->fileds_l->author)
					> main_struct->max_fileds->max_name)
				main_struct->max_fileds->max_name = ft_strlen(
						node->fileds_l->author);
			check_max_size_continue(main_struct, node);
		}
		node = node->next;
	}
}

void	print_st_rdev(t_fileds_l *l_fileds, t_main *main_struct)
{
	fill_spase_before(ft_strlen(l_fileds->major_st_rdev),
			main_struct->max_fileds->max_major);
	if (l_fileds->major_st_rdev != NULL)
	{
		ft_putstr(l_fileds->major_st_rdev);
		ft_putstr(", ");
	}
	else
		fill_spase_before(0, main_struct->max_fileds->max_major);
	fill_spase_before(ft_strlen(l_fileds->minor_st_rdev),
			main_struct->max_fileds->max_minor);
	if (l_fileds->minor_st_rdev != NULL)
	{
		ft_putstr(l_fileds->minor_st_rdev);
		ft_putchar(' ');
	}
	else
		fill_spase_before(0, main_struct->max_fileds->max_minor);
}

void	print_file_stat_continue(t_fileds_l *l_fileds, t_main *main_struct)
{
	if (l_fileds->st_size != NULL)
	{
		if ((main_struct->max_fileds->max_size)
				> (main_struct->max_fileds->max_major
					+ main_struct->max_fileds->max_minor))
			fill_spase_before(ft_strlen(l_fileds->st_size),
					main_struct->max_fileds->max_size);
		else
			fill_spase_before(ft_strlen(l_fileds->st_size),
					(main_struct->max_fileds->max_major
					+ 2 + main_struct->max_fileds->max_minor));
		ft_putstr(l_fileds->st_size);
		ft_putchar(' ');
	}
	else
		print_st_rdev(l_fileds, main_struct);
	insert_spase(l_fileds, ft_strlen(l_fileds->date),
			main_struct->max_fileds->max_time);
	ft_putstr(l_fileds->date);
	ft_putchar(' ');
}

void	print_file_stat(t_fileds_l *l_fileds, t_main *main_struct)
{
	ft_putstr(l_fileds->file_type);
	ft_putstr(l_fileds->permission);
	ft_putstr("  ");
	fill_spase_before(ft_strlen(l_fileds->st_nlink),
			main_struct->max_fileds->max_nlink);
	ft_putstr(l_fileds->st_nlink);
	ft_putchar(' ');
	ft_putstr(l_fileds->author);
	fill_spase_after(ft_strlen(l_fileds->author),
			main_struct->max_fileds->max_name);
	ft_putstr("  ");
	ft_putstr(l_fileds->group_name);
	fill_spase_after(ft_strlen(l_fileds->group_name),
			main_struct->max_fileds->max_group);
	ft_putstr("  ");
	print_file_stat_continue(l_fileds, main_struct);
	if (l_fileds->target_name)
		ft_putstr(l_fileds->d_name);
	else
		ft_putendl(l_fileds->d_name);
	if (l_fileds->file_type[0] == 'l')
	{
		ft_putstr(" -> ");
		ft_putendl(l_fileds->target_name);
	}
}
