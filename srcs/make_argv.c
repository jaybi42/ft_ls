/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:12:17 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/23 18:59:21 by jguthert         ###   ########.fr       */
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

static int	print_argv(t_list *list, t_arg *arg_list)
{
	t_list *new_list;
	t_list *tamp;

	if (list->next == NULL && S_ISDIR(((t_file *)list->content)->mode) == 1)
		return (base_list(list, arg_list, 1));
	while (list != NULL && S_ISDIR(((t_file *)list->content)->error) != 0)
	{
		print_error(((t_file *)list->content)->name,
					((t_file *)list->content)->error);
		list = list->next;
	}
	if (list != NULL)
	{
		// split list in sort argv
		print_ls(new_list, arg_list);
		return (base_list(new_list, arg_list, 0));
	}
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
		if (sort_list(&begin_list, arg_list) == 1)
			return (1);
		if (arg_list->arg[5] == 0)
		{
			if (sort_argv(&begin_list) == 1)
				return (1);
		}
	}
	if (print_argv(begin_list, arg_list) == 1)
		return (1);
	return (0);
}
