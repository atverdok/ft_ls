/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 11:21:41 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/04 09:43:09 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		make_print(t_main *main_struct, t_stack **stack_head)
{
	if (main_struct->options->l)
		print_list(main_struct->head, stack_head, main_struct,
				print_file_stat);
	else
		print_list(main_struct->head, stack_head, main_struct, print_name);
}

void		print_path(char *path, t_boolean *flag, int err, size_t len_stack)
{
	if (*flag)
	{
		if (len_stack > 1 || err)
		{
			ft_putstr(path);
			ft_putendl(":");
		}
		*flag = FALSE;
	}
	else
		print_path_l(path);
}

void		print_in_files(t_main *main_struct, t_stack *stack_head, int *err,
		t_boolean *flag)
{
	if (main_struct->head)
	{
		check_max_size_and_size(main_struct);
		make_print(main_struct, &stack_head);
		main_struct->head = NULL;
		(*err)++;
		*flag = FALSE;
	}
}

void		make_priint_stack(t_main *main_struct, t_stack *stack_head, int err)
{
	char		*path;
	t_boolean	flag;
	size_t		len_stack;

	flag = TRUE;
	print_in_files(main_struct, stack_head, &err, &flag);
	len_stack = get_len_stack(stack_head);
	path = pop_stack(&stack_head);
	while (path)
	{
		main_struct->total = 0;
		ft_bzero(main_struct->max_fileds, sizeof(t_max_fileds));
		print_path(path, &flag, err, len_stack);
		main_struct->head = ft_list_dir(path, main_struct);
		ft_strdel(&path);
		check_max_size_and_size(main_struct);
		print_total_l(main_struct);
		make_print(main_struct, &stack_head);
		path = pop_stack(&stack_head);
	}
}

int			main(int argc, char **argv)
{
	t_main		*main_struct;
	t_stack		*tmp;
	int			i_err[2];

	tmp = NULL;
	main_struct = create_main_struct();
	i_err[0] = 0;
	i_err[1] = 0;
	make_parce_options(&i_err[0], argc, argv, main_struct);
	while (i_err[0] < argc)
	{
		if (parse_argument(i_err, argv, main_struct, &tmp))
		{
			print_perror((void *)argv[i_err[0]]);
			i_err[1]++;
		}
		i_err[0]++;
	}
	if (!i_err[1])
		sorted_insert_stack(&tmp, create_stack_node(ft_strdup(".")));
	make_priint_stack(main_struct, tmp, i_err[1]);
	return (0);
}
