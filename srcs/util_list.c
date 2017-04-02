/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 14:02:24 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 14:03:48 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_node		*new_node(t_fileds_l *fileds_l)
{
	t_node *tmp;

	tmp = (t_node *)ft_memalloc(sizeof(t_node));
	tmp->next = NULL;
	tmp->fileds_l = fileds_l;
	return (tmp);
}

t_fileds_l	*list_pop(t_node **head)
{
	t_node		*prev;
	t_fileds_l	*fileds_l;

	if ((*head) == NULL)
		return (NULL);
	prev = (*head);
	fileds_l = prev->fileds_l;
	(*head) = (*head)->next;
	free(prev);
	return (fileds_l);
}

void		sorted_insert(t_node **head, t_node *new_node, t_boolean r,
		int (*cmp)(t_fileds_l *, t_fileds_l *, t_boolean))
{
	t_node *current;

	if (*head == NULL || cmp((*head)->fileds_l, new_node->fileds_l, r))
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL &&
				!cmp(current->next->fileds_l, new_node->fileds_l, r))
			current = current->next;
		new_node->next = current->next;
		current->next = new_node;
	}
}
