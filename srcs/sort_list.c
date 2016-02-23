/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 15:40:27 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/23 23:03:13 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void sort_mtime(t_list **list)
{
	return ;
}

static void sort_lexi(t_list **list)
{
	return ;
}

static void sort_rlexi(t_list **list)
{
	return ;
}
/*
void		ft_lst_mid(t_list **begin, t_list *list)
{
	t_list	*tamp;
	t_list	*prev;

	tamp = *begin;
	prev = *begin;
	if (tamp->is_dir == 1)
		ft_lstadd(begin, list);
	while (1)
	{
		if (tamp->is_dir == 1)
		{
			prev->next = list;
			list->next = tamp;
		}
		if (tamp->next == NULL)
			ft_lstadd_back(begin, list);
		prev = tamp;
		tamp = tamp->next;
	}
}

void		sort_argv(t_list **list)
{
	t_list	*begin;
	t_list	*to_sort;

	to_sort = *list;
	while (begin->file.is_fil == 0 && begin->file.is_dir == 0)
	{
		prev = begin;
		to_sort = begin->next;
	}
	while (begin->file.is_fil == 1)
	{
	}
	while (begin->file.is_dir == 1)
	{

	}
	return ;
	}*/


void		sort_list(t_list **list, t_arg *arg_list)
{
/*	if (arg_list->arg[3] == 1)
		sort_rlexi(list);
	else if (arg_list->arg[4] == 1)
		sort_mtime(list);
	else
	sort_lexi(list);*/
}
