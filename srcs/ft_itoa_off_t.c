/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 13:24:51 by atverdok          #+#    #+#             */
/*   Updated: 2017/03/06 13:25:56 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

#define A(x) ((x < 0) ? -(x) : (x))

static off_t	len_str(off_t nbr)
{
	off_t len;

	len = 1;
	while ((nbr = nbr / 10))
		len++;
	return (len);
}

static void		make_str(char *str, off_t nbr, int *i)
{
	if (nbr > 9 || nbr < -9)
		make_str(str, nbr / 10, i);
	str[(*i)++] = (char)(A(nbr % 10) + '0');
}

char			*ft_itoa_off_t(off_t nbr)
{
	char	*str;
	off_t	len;
	int		i;

	len = len_str(nbr);
	if (!(str = (char *)malloc(sizeof(char *) * len)))
		return (0);
	i = 0;
	if (nbr < 0)
		str[i++] = '-';
	make_str(str, nbr, &i);
	str[i] = '\0';
	return (str);
}
