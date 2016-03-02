/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 15:40:27 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/02 17:30:13 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void test_list(t_list **begin_list)
{
    t_list *drive;

    drive = *begin_list;
	while (drive != NULL)
	{
		if (((t_file *)drive->content)->is_dir == 1)
			printf("\n%s:\n", ((t_file *)drive->content)->name);
		else
			printf("%s\n", ((t_file *)drive->content)->name);
		drive = drive->next;
	}
}

static void link_to_front(t_list **list, t_list *link)
{
	t_list	*prev;

	prev = *list;
	while (prev->next != link)
		prev = prev->next;
	prev->next = link->next;
	link->next = *list;
	*list = link;
}

static void sort_time(t_list **list, bool crescent)
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
			if (crescent && ((t_file *)tamp->content)->mtime >
							((t_file *)link->content)->mtime)
				link = tamp;
			else if (!crescent && ((t_file *)tamp->content)->mtime <
									((t_file *)link->content)->mtime)
				link = tamp;
			tamp = tamp->next;
		}
		if (begin == link)
			begin = begin->next;
		if (link != *list)
			link_to_front(list, link);
	}
	return ;
}

static void sort_lexi(t_list **list, bool crescent)
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
