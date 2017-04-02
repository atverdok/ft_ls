/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 11:21:41 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 12:01:08 by atverdok         ###   ########.fr       */
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

void		make_priint_stack(t_main *main_struct, t_stack *stack_head, int err)
{
	char		*path;
	t_boolean	flag;
	size_t		len_stack;

	flag = TRUE;
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
	int			i;
	t_main		*main_struct;
	t_stack		*tmp;

	tmp = NULL;
	main_struct = create_main_struct();
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1])
			parse_options(argv[i], main_struct);
		else
			break ;
	}
	while (i < argc)
	{
		sorted_insert_stack(&tmp, create_stack_node(ft_strdup(argv[i])));
		i++;
	}
	make_queue(main_struct, tmp);
	return (0);
}
