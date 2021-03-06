/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 12:22:59 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/04 09:48:13 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		parse_options(char *str, t_main *main_struct)
{
	while (str++ && *str != '\0')
	{
		if (*str == 'l')
			main_struct->options->l = TRUE;
		else if (*str == 'R')
			main_struct->options->up_r = TRUE;
		else if (*str == 'a')
			main_struct->options->a = TRUE;
		else if (*str == 'r')
			main_struct->options->r = TRUE;
		else if (*str == 't')
			main_struct->options->t = TRUE;
		else if (*str == '1' || ((*(str - 1) == '-') && (*str == '-')
					&& (*(str + 1) != '-')))
			continue ;
		else
		{
			illegal_options_error(str);
			usage_error();
			exit(1);
		}
	}
}

char		*make_parce_options(t_stack **tmp_arg,
		t_main *main_struct)
{
	char *arg;

	arg = pop_stack(tmp_arg);
	while (arg)
	{
		if (arg[0] == '-' && arg[1])
			parse_options(arg, main_struct);
		else
			break ;
		arg = pop_stack(tmp_arg);
	}
	return (arg);
}

t_boolean	parse_argument(int *err, char *arg,
		t_main *main_struct, t_stack **tmp)
{
	struct stat stat_f;
	t_fileds_l	*fileds_l;
	t_node		*head;

	head = (main_struct->head) ? main_struct->head : NULL;
	if (!lstat(arg, &stat_f))
	{
		if ((fileds_l = get_stat_single_file(ft_strdup(arg), stat_f))
				!= NULL && ((stat_f.st_mode & S_IFMT) != S_IFDIR))
		{
			(main_struct->options && main_struct->options->t)
			? sorted_insert(&head, new_node(fileds_l),
							main_struct->options->r, cmp_date)
			: sorted_insert(&head, new_node(fileds_l),
							main_struct->options->r, cmp_name);
			main_struct->head = head;
		}
		else
			sorted_insert_stack(tmp,
					create_stack_node(ft_strdup(arg)));
		(*err)++;
		return (FALSE);
	}
	return (TRUE);
}
