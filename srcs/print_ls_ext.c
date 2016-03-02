/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 18:02:25 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/02 18:24:10 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"



int		nbrlen(uint64_t nbr)
{
	int i;

	i = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

void	print_total(t_list *list)
{
	uint64_t size;

	size = 0;
	while (list != NULL)
	{
		size += ((t_file *)list->content)->size;
		list = list->next;
	}
	ft_putstr("total ");
	ft_putnbr(size / 512);
	ft_putchar('\n');
}

void	print_name(char *name)
{
	if (name != NULL)
		ft_putstr(name);
	ft_putstr("  ");
}

void	print_nlink(uint16_t nlink)
{
	ft_putnbr(nlink);
	ft_putstr("  ");
}
