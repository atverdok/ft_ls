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

void		make_parce_options(int *i, int argc, char **argv,
		t_main *main_struct)
{
	while (++(*i) < argc)
	{
		if (argv[*i][0] == '-' && argv[*i][1])
			parse_options(argv[*i], main_struct);
		else
			break ;
	}
}

t_boolean	parse_argument(int *i_err, char **argv,
		t_main *main_struct, t_stack **tmp)
{
	struct stat stat_f;
	t_fileds_l	*fileds_l;
	t_node		*head;

	head = NULL;
	if (!lstat(argv[i_err[0]], &stat_f))
	{
		if ((fileds_l = get_stat_single_file(ft_strdup(argv[i_err[0]]), stat_f))
				!= NULL && ((stat_f.st_mode & S_IFMT) != S_IFDIR))
		{
			if (main_struct->options && main_struct->options->t)
				sorted_insert(&head, new_node(fileds_l),
						main_struct->options->r, cmp_date);
			else
				sorted_insert(&head, new_node(fileds_l),
						main_struct->options->r, cmp_name);
			main_struct->head = head;
		}
		else
			sorted_insert_stack(tmp,
					create_stack_node(ft_strdup(argv[i_err[0]])));
		i_err[1]++;
		return (FALSE);
	}
	return (TRUE);
}
