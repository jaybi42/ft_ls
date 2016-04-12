/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:12:17 by jguthert          #+#    #+#             */
/*   Updated: 2016/04/12 17:22:16 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

void			free_list(void *content, size_t size)
{
	t_file	*file;
	char	*path;
	char	*lnk;

	(void)size;
	file = (t_file *)content;
	if (file != NULL)
	{
		path = (char *)file->path;
		lnk = (char *)file->lnk_path;
		if (path != NULL)
			ft_strdel(&path);
		if (lnk != NULL)
			ft_strdel(&lnk);
		free(content);
		content = NULL;
	}
}

static void		print_fakelist(t_list **list)
{
	t_list	*cur;
	t_list	*prev;

	prev = *list;
	while (prev != NULL && ((t_file *)prev->content)->error != 0)
	{
		print_error(((t_file *)prev->content)->name,
					((t_file *)prev->content)->error);
		*list = (*list)->next;
		ft_lstdelone(&prev, free_list);
		prev = *list;
	}
	while (prev != NULL && prev->next != NULL)
	{
		cur = prev->next;
		if (((t_file *)cur->content)->error != 0)
		{
			prev->next = cur->next;
			print_error(((t_file *)cur->content)->name,
						((t_file *)cur->content)->error);
			ft_lstdelone(&cur, free_list);
		}
		else
			prev = prev->next;
	}
}

static t_list	*get_reglist(t_list **list, bool l_opt)
{
	t_list  *reg_list;
	t_list	*prev;
	t_list	*cur;

	reg_list = NULL;
	prev = *list;
    while (prev != NULL && (S_ISREG(((t_file *)prev->content)->mode == 1) ||
							(((t_file *)prev->content)->lnk_path != NULL && l_opt == 1)))
	{
		*list = (*list)->next;
		ft_lstadd_last(&reg_list, prev);
		prev = *list;
	}
	while (prev != NULL && prev->next != NULL)
	{
		cur = prev->next;
		if (S_ISREG(((t_file *)cur->content)->mode) == 1 ||
			(((t_file *)prev->content)->lnk_path != NULL && l_opt == 1))
		{
			prev->next = cur->next;
			ft_lstadd_last(&reg_list, cur);
		}
		else
			prev = prev->next;
	}
	return (reg_list);
}

static int		sort_argv(t_list **list, t_arg *arg_list)
{
	t_list	*reg_list;
	bool	first;
	bool	alone;

	first = 1;
	if (*list != NULL)
		print_fakelist(list);
	if (*list != NULL)
	{
		reg_list = get_reglist(list, arg_list->arg[9]);
		if (reg_list != NULL)
		{
			print_ls(reg_list, arg_list);
			ft_lstdel(&reg_list, free_list);
			first = 0;
		}
	}
	alone = 0;
	if ((*list) != NULL && (*list)->next == NULL)
		alone = 1;
	if (*list != NULL)
		return (base_list(*list, arg_list, alone, first));
	else
		return (0);
}

int				argv_to_list(char **argv, int argi, t_arg *arg_list)
{
	t_list	*begin_list;

	begin_list = NULL;
	if (add_list(argv[argi--], arg_list, &begin_list) == 1)
		return (1);
	while (argi > 0)
	{
		if (add_list(argv[argi--], arg_list,  &begin_list) == 1)
			return (1);
	}
	if (begin_list->next != NULL)
	{
		if (arg_list->arg[5] == 0)
		{
			if (sort_list(&begin_list, arg_list) == 1)
				return (1);
		}
	}
	if (sort_argv(&begin_list, arg_list) == 1)
		return (1);
	return (0);
}
