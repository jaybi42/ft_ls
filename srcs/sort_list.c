/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 15:40:27 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/24 20:28:54 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void test_list(t_list **begin_list)
{
    t_list *drive;

    drive = *begin_list;
    while (drive != NULL)
    {
		printf("name: [%s]\n", ((t_file *)drive->content)->name);
		drive = drive->next;
    }
}

static void sort_mtime(t_list **list)
{
	return ;
}

static void put_link(t_list **list, t_list *link)
{
	t_list	*tamp;
	t_list	*prev;

	tamp = (*list)->next;
	prev = *list;
	while (tamp != link)
	{
		prev = prev->next;
		tamp = tamp->next;
	}
	prev->next = link->next;
	link->next = *list;
	*list = link;
}


static void sort_lexi(t_list **list, bool crescent)
{
	t_list	*tamp;
	t_list	*first;
	t_list	*begin;


	begin = *list;
	while (begin != NULL)
	{
		tamp = begin->next;
		first = begin;
		while (tamp != NULL)
		{
			if (crescent && ft_strcmp(((t_file *)tamp->content)->name,
									  ((t_file *)first->content)->name) > 0)
				first = tamp;
			else if (!crescent && ft_strcmp(((t_file *)tamp->content)->name,
											((t_file *)first->content)->name) < 0)
				first = tamp;
			tamp = tamp->next;
		}
		if (begin == first)
			begin = begin->next;
		if (first != *list)
			put_link(list, first);
	}
}

int			sort_list(t_list **list, t_arg *arg_list)
{
	if (arg_list->arg[3] == 1)
		sort_lexi(list, 0);
	else if (arg_list->arg[4] == 1)
		sort_mtime(list);
	else
		sort_lexi(list, 1);
	return (0);
}
