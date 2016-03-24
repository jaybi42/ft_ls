/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:12:17 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/24 18:18:49 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

void		free_list(void *content, size_t size)
{
	t_file	*file;
	char	*path;

	(void)size;
	file = (t_file *)content;
	if (file != NULL)
	{
		path = (char *)file->path;
		if (path != NULL)
			ft_strdel(&path);
		free(content);
		content = NULL;
	}
}

static void	print_fakelist(t_list **list)
{
	t_list	*cur;
	t_list	*prev;

	prev = *list;
	while (prev != NULL && ((t_file *)prev->content)->error != 0)
	{
		*list = *list->next;
		ft_lstdelone(prev, free_list);
		prev = *list;
	}
	while (prev != NULL && prev->next != NULL)
	{
		cur = prev->next;
		if (((t_file *)cur->content)->error) != 0)
		{
			print_error(((t_file *)cur->content)->name,
						((t_file *)cur->content)->error);
			prev = cur->next;
			ft_lstdelone(cur, free_list);
		}
		else
			prev = prev->next;
	}
}

static bool	print_reglist(t_list **list, t_arg *arg_list)
{
	return (1);
}


static int	sort_argv(t_list **list, t_arg *arg_list)
{
	t_list	*begin_list;
    bool    reg;

	begin_list != NULL;
    while (*list != NULL)
        print_fakelist(list);
    if (*list != NULL)
        reg = print_reglist(list, arg_list);
    if (reg == 1 && *list != NULL)
        ft_putchar('\n');
	if ((*list)->next == NULL && S_ISDIR(((t_file *)(*list)->content)->mode) == 1)
		return (base_list(*list, arg_list, 1));
	else if (list != NULL)
		return (base_list(*list, arg_list, 0));
	else
		return (0);
}

int			argv_to_list(char **argv, int argi, t_arg *arg_list)
{
	t_list	*begin_list;

	begin_list = NULL;
	if (add_list(argv[argi--], &begin_list) == 1)
		return (1);
	while (argi > 0)
	{
		if (add_list(argv[argi--], &begin_list) == 1)
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
	if (sort_argv(&begin_list) == 1)
		return (1);
	if (print_argv(begin_list, arg_list) == 1)
		return (1);
	return (0);
}
