/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 18:52:50 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/25 18:55:08 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void print_error(char *name)
{
	ft_putstr("ls: ");
	ft_putstr(name);
	ft_putstr(": ");
	ft_putendl(strerror(errno));
}

void		print_ls(t_list *list, t_arg *arg_list)
{
	return ;
}
