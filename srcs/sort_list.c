/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 15:40:27 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/24 16:36:58 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void sort_mtime(t_list **list, int link)
{
	return ;
}

static void sort_lexi(t_list **list, int link)
{
	t_list	*begin;
	t_list	*new_list;
	t_list	*tamp;

	begin = *list;
	new_list = *list;
	while (link-- > 0)
	{
		while (begin != NULL)
		{

		}
	}
	*list = new_list;
	return ;
}

static void sort_rlexi(t_list **list, int link)
{
	return ;
}

static int	count_link(t_list **list)
{
	int		link;
	t_list	*tamp;

	tamp = *list;
	while (tamp != NULL)
	{
		link++;
		tamp = tamp->next;
	}
	return (link);
}

int			sort_list(t_list **list, t_arg *arg_list)
{
	int link;

	link = count_link(list);
	if (arg_list->arg[3] == 1)
		sort_rlexi(list, link);
	else if (arg_list->arg[4] == 1)
		sort_mtime(list, link);
	else
		sort_lexi(list, link);
	return (0);
}
