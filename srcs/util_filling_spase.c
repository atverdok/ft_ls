/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_filling_spase.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 14:30:50 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 14:30:55 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	fill_spase_before(size_t len, size_t n)
{
	while (n > len)
	{
		ft_putchar(' ');
		n--;
	}
}

void	fill_spase_after(size_t len, size_t n)
{
	while (n > len)
	{
		ft_putchar(' ');
		n--;
	}
}

void	insert_spase(t_fileds_l *l_fileds, size_t len, size_t n)
{
	char *str;

	str = (char *)ft_memalloc(14);
	if (n > len)
	{
		ft_strncpy(str, l_fileds->date, 4);
		ft_strncat(str, " ", 1);
		ft_strncat(str, (l_fileds->date + 4), ft_strlen((l_fileds->date + 4)));
		free(l_fileds->date);
		l_fileds->date = str;
	}
}
