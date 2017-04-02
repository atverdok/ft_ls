/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 14:37:26 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 14:37:31 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	push_stack(t_stack **head, char *path)
{
	t_stack *tmp;

	tmp = ft_memalloc(sizeof(t_stack));
	if (tmp == NULL)
	{
		perror("push_stack");
		exit(1);
	}
	tmp->next = *head;
	tmp->path = path;
	*head = tmp;
}

char	*pop_stack(t_stack **head)
{
	t_stack	*out;
	char	*path;

	if ((*head) == NULL)
	{
		return (NULL);
	}
	out = *head;
	*head = (*head)->next;
	path = out->path;
	free(out);
	return (path);
}

void	push_global_stack(t_stack **stack, t_stack **stack_tmp)
{
	char *path;

	if (stack_tmp)
	{
		path = pop_stack(stack_tmp);
		while (path)
		{
			push_stack(stack, path);
			path = pop_stack(stack_tmp);
		}
	}
}

t_stack	*create_stack_node(char *path)
{
	t_stack *tmp;

	tmp = ft_memalloc(sizeof(t_stack));
	if (tmp == NULL)
	{
		perror("create_stack_node");
		exit(1);
	}
	tmp->next = NULL;
	tmp->path = path;
	return (tmp);
}

void	sorted_insert_stack(t_stack **head, t_stack *new_node)
{
	t_stack *current;

	if (*head == NULL || (ft_strcmp((*head)->path, new_node->path) >= 0))
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL &&
				(ft_strcmp(current->next->path, new_node->path) < 0))
			current = current->next;
		new_node->next = current->next;
		current->next = new_node;
	}
}
