/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 12:47:23 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 12:47:28 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	usage_error(void)
{
	ft_putstr_fd("usage: ./ft_ls [-lartR] [file ...]\n", 2);
}

void	illegal_options_error(char *str)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	print_perror(void *value)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror((char *)value);
}
