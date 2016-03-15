/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:33:03 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/15 20:41:33 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <string.h>

void	print_error(char *name, int error)
{
	(void)error;
	if (name == NULL)
		return ;
	ft_putstr("ls: ");
	ft_putstr(name);
	ft_putstr(": ");
	perror("");
//	ft_putendl(strerror(error));
}
