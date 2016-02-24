/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 15:40:27 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/24 23:31:17 by jguthert         ###   ########.fr       */
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
										((t_file *)link->content)->name) > 0)
				link = tamp;
			else if (!crescent && ft_strcmp(((t_file *)tamp->content)->name,
										((t_file *)link->content)->name) < 0)
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
	if (arg_list->arg[3] == 1)
		sort_lexi(list, 0);
	else if (arg_list->arg[4] == 1)
		sort_mtime(list);
	else
		sort_lexi(list, 1);
//	test_list(list);
	return (0);
}
