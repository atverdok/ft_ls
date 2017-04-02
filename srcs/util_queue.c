/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 11:50:44 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/02 11:50:51 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	queue_or_error(char *path, t_boolean *flag, t_stack **stack_head,
		int *err_count)
{
	DIR	*dirp;

	if ((dirp = opendir(path)) != NULL)
	{
		push_queue_bak(stack_head, path);
		(void)closedir(dirp);
	}
	else
	{
		print_perror((void *)path);
		(*err_count)++;
	}
	*flag = FALSE;
}

void	make_queue(t_main *main_struct, t_stack *tmp)
{
	t_boolean	flag;
	t_stack		*stack_head;
	char		*path;
	int			err_count;

	flag = TRUE;
	stack_head = NULL;
	err_count = 0;
	path = pop_stack(&tmp);
	while (path)
	{
		queue_or_error(path, &flag, &stack_head, &err_count);
		path = pop_stack(&tmp);
	}
	if (flag)
		push_queue_bak(&stack_head, ft_strdup("."));
	make_priint_stack(main_struct, stack_head, err_count);
}

void	push_queue_bak(t_stack **head, char *path)
{
	t_stack *tmp;
	t_stack **last;

	tmp = ft_memalloc(sizeof(t_stack));
	if (tmp == NULL)
	{
		perror("push_queue_bak");
		exit(1);
	}
	tmp->next = NULL;
	tmp->path = path;
	if (*head == NULL)
	{
		*head = tmp;
		return ;
	}
	last = head;
	while (*last && (*last)->next)
		*last = (*last)->next;
	(*last)->next = tmp;
}

size_t	get_len_stack(t_stack *stack)
{
	size_t	counter;
	t_stack	*tmp;

	counter = 0;
	tmp = stack;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}
