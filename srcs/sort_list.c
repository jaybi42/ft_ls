/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 15:40:27 by jguthert          #+#    #+#             */
/*   Updated: 2016/04/26 16:23:51 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	link_to_front(t_list **list, t_list *link)
{
	t_list	*prev;

	prev = *list;
	while (prev->next != link)
		prev = prev->next;
	prev->next = link->next;
	link->next = *list;
	*list = link;
}

static bool	link_toswap(t_file *link_f, t_file *tamp_f, bool crescent)
{
	int		ret;

	if (link_f->time == tamp_f->time)
		ret = (link_f->nano >= tamp_f->nano);
	else
		ret = (link_f->time > tamp_f->time);
	if (ret == 0 && crescent)
		return (1);
	else if (!crescent && ret == 1)
		return (1);
	return (0);
}

static void	sort_time(t_list **list, bool crescent)
{
	t_list	*tamp;
	t_list	*link;
	t_list	*begin;

	begin = *list;
	while (begin != NULL)
	{
		tamp = begin->next;
		link = begin;
		while (tamp != NULL)
		{
			if (link_toswap(((t_file *)link->content),
							((t_file *)tamp->content), crescent) == 1)
				link = tamp;
			tamp = tamp->next;
		}
		if (begin == link)
			begin = begin->next;
		if (link != *list)
			link_to_front(list, link);
	}
}

static void	sort_lexi(t_list **list, bool crescent)
{
	t_list	*tamp;
	t_list	*link;
	t_list	*begin;

	begin = *list;
	while (begin != NULL)
	{
		tamp = begin->next;
		link = begin;
		while (tamp != NULL)
		{
			if (crescent && ft_strcmp(((t_file *)tamp->content)->name,
										((t_file *)link->content)->name) < 0)
				link = tamp;
			else if (!crescent && ft_strcmp(((t_file *)tamp->content)->name,
										((t_file *)link->content)->name) > 0)
				link = tamp;
			tamp = tamp->next;
		}
		if (begin == link)
			begin = begin->next;
		if (link != *list)
			link_to_front(list, link);
	}
}

int			sort_list(t_list **list, t_arg *arg_list)
{
	if (arg_list->arg[5] == 1)
		return (0);
	else if (arg_list->arg[12] == 1)
		sort_time(list, arg_list->arg[11]);
	else
		sort_lexi(list, arg_list->arg[11]);
	return (0);
}
