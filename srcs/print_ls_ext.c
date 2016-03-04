/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 18:02:25 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/04 20:09:56 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dirname(t_list *link)
{
	if (S_ISDIR(((t_file *)link->content)->mode) == 1)
	{
		ft_putstr(((t_file *)link->content)->path);
		ft_putendl(":");
	}
	else if (((t_file *)link->content)->is_fake == 1)
	{
		ft_putstr("ls: ");
		ft_putstr(((t_file *)link->content)->name);
		ft_putendl(": No such file or directory");
	}
	else
		print_name(((t_file *)link->content)->name, 0);
}

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
		size = size + (((t_file *)list->content)->size);
		list = list->next;
	}
	ft_putstr("total ");
	ft_putnbr(size / 512);
	ft_putchar('\n');
}

void	print_name(char *name, bool is_lnk)
{
	if (name != NULL)
		ft_putstr(name);
	if (is_lnk == 1)
	{
		ft_putstr(" -> ");
		ft_putstr(name);
	}
	ft_putchar('\n');
}

void	print_nlink(uint16_t nlink)
{
	ft_putnbr(nlink);
	ft_putstr("  ");
}
