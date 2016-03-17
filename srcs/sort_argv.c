/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 14:59:31 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/17 18:55:45 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	link_to_fakefile(t_list **list, t_list *link)
{
	t_list	*prev;
	t_list	*tamp;

	if (link == *list)
		return ;
	prev = *list;
	while (prev->next != link)
		prev = prev->next;
	if (((t_file *)prev->content)->error == 0)
		return ;
	prev->next = link->next;
	prev = *list;
	tamp = (*list)->next;
	while (tamp != NULL)
	{
		if (((t_file *)tamp->content)->error == 0)
			break ;
		tamp = tamp->next;
		prev = prev->next;
	}
	link->next = tamp;
	prev->next = link;
}

static void	link_to_back(t_list **list, t_list *link)
{
	t_list	*prev;

	prev = *list;
	if (link->next == NULL)
		return ;
	if (link == *list)
		*list = link->next;
	else
	{
		while (prev->next != link)
			prev = prev->next;
		prev->next = link->next;
	}
	while (prev->next != NULL)
		prev = prev->next;
	prev->next = link;
	link->next = NULL;
}

static int	count_link(t_list **list)
{
	int		count;
	t_list	*link;

	count = 0;
	link = *list;
	while (link != NULL)
	{
		link = link->next;
		count++;
	}
	return (count);
}

int			sort_argv(t_list **list)
{
	t_list	*link;
	t_list	*next_link;
	int		i;

	i = count_link(list);
	next_link = (*list)->next;
	link = *list;
	while (i-- > 0)
	{
		if (((t_file *)link->content)->error != 0)
			link_to_fakefile(list, link);
		else if (S_ISDIR(((t_file *)link->content)->mode) == 1)
			link_to_back(list, link);
		link = next_link;
		if (next_link != NULL)
			next_link = next_link->next;
	}
	return (0);
}
