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
