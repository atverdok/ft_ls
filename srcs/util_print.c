/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 14:07:17 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 14:16:53 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_name(t_fileds_l *l_fileds, t_main *main_struct)
{
	if (main_struct && l_fileds)
		ft_putendl(l_fileds->d_name);
}

void	print_list(t_node *head, t_stack **stack, t_main *main_struct,
		void (*print)(t_fileds_l *, t_main *))
{
	t_stack		*stack_tmp;
	t_fileds_l	*tmp;

	tmp = list_pop(&head);
	stack_tmp = NULL;
	while (tmp)
	{
		if (main_struct->options && main_struct->options->up_r
				&& tmp->ful_path
				&& (ft_strcmp(tmp->d_name, "..")
					&& ft_strcmp(tmp->d_name, ".")))
			push_stack(&stack_tmp, ft_strdup(tmp->ful_path));
		print(tmp, main_struct);
		del_t_fileds_l(tmp);
		tmp = list_pop(&head);
	}
	push_global_stack(stack, &stack_tmp);
}

void	print_total_l(t_main *main_struct)
{
	if (main_struct->head && main_struct->options->l)
	{
		ft_putstr("total ");
		ft_putnbr((int)main_struct->total);
		ft_putchar('\n');
	}
}

void	print_path_l(const char *path)
{
	ft_putstr("\n");
	ft_putstr(path);
	ft_putendl(":");
}
