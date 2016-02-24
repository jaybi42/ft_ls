/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 14:59:31 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/24 23:39:01 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	link_to_fakefile(t_list **list, t_list *link)
{
	t_list	*prev;

	prev = *list;
	while (prev->next != link)
		prev = prev->next;
	prev->next = link->next;
	prev = *list;
	while (((t_file *)(prev->next)->content)->is_dir == 0
		   && ((t_file *)(prev->next)->content)->is_fil == 0)
		prev = prev->next;
	link->next = prev->next;
	prev->next = link;
}

static void	link_to_back(t_list **list, t_list *link)
{
	t_list	*prev;

	if (link->next == NULL)
		return ;
	prev = *list;
	while (prev->next != link)
		prev = prev->next;
	prev->next = link->next;
	while (prev->next != NULL)
		prev = prev->next;
	prev->next = link;
	link->next = NULL;
}

int			sort_argv(t_list **list)
{
	t_list	*link;

	link = (*list)->next;
	while (link != NULL)
	{
		if (((t_file *)link->content)->is_fil == 0 && ((t_file *)link->content)->is_dir == 0)
			link_to_fakefile(list, link);
		else if (((t_file *)link->content)->is_dir == 1)
			link_to_back(list, link);
	}
	return (0);
}
