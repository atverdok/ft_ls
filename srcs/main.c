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
		if (len_stack > 1 || err > 1)
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
	t_stack		*tmp_arg[2];
	int			err;
	char		*arg;

	tmp_arg[0] = NULL;
	tmp_arg[1] = NULL;
	main_struct = create_main_struct();
	err = 0;
	while (argc-- > 1)
		sorted_insert_stack(&tmp_arg[1], create_stack_node(argv[argc]));
	arg = make_parce_options(&tmp_arg[1], main_struct);
	while (arg)
	{
		if (parse_argument(&err, arg, main_struct, &tmp_arg[0]))
		{
			print_perror((void *)arg);
			err++;
		}
		arg = pop_stack(&tmp_arg[1]);
	}
	if (!err)
		sorted_insert_stack(&tmp_arg[0], create_stack_node(ft_strdup(".")));
	make_priint_stack(main_struct, tmp_arg[0], err);
	return (0);
}
