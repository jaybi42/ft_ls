/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:33:03 by jguthert          #+#    #+#             */
/*   Updated: 2016/04/12 19:25:35 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	print_error(char *name, int error)
{
	(void)error;
	if (name == NULL)
		return ;
	ft_putstr("ls: ");
	ft_putstr(name);
	ft_putstr(": ");
	perror("");
}
