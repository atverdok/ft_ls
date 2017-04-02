/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 12:22:59 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/01 12:41:26 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	parse_options(char *str, t_main *main_struct)
{
	while (str++ && *str != '\0')
	{
		if (*str == 'l')
			main_struct->options->l = TRUE;
		else if (*str == 'R')
			main_struct->options->up_r = TRUE;
		else if (*str == 'a')
			main_struct->options->a = TRUE;
		else if (*str == 'r')
			main_struct->options->r = TRUE;
		else if (*str == 't')
			main_struct->options->t = TRUE;
		else if (*str == '1' || ((*(str - 1) == '-') && (*str == '-')
					&& (*(str + 1) != '-')))
			continue ;
		else
		{
			illegal_options_error(str);
			usage_error();
			exit(1);
		}
	}
}
