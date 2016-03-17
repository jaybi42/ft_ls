/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:12:17 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/17 18:18:42 by jguthert         ###   ########.fr       */
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

static int	one_list(t_list *list, t_arg *arg_list)
{
    t_list  *link;
    t_list  *new_list;
    int     ret;

    link = list;
    new_list = NULL;
    while (link != NULL)
    {
        if (S_ISDIR(((t_file *)link->content)->mode) == 1)
        {
            ret = make_list(((t_file *)link->content)->path, arg_list, &new_list);
            if (ret == 1)
				return (1);
            sort_list(&new_list, arg_list);
			print_ls(new_list, arg_list);
            if (arg_list->arg[1] == 1)
                base_list(new_list, arg_list);
        }
        if (new_list != NULL)
            ft_lstdel(&new_list, free_list);
        link = link->next;
    }
    return (0);
}

static int	print_argv(t_list *list, t_arg *arg_list)
{
	t_file	*file;

	if (list->next == NULL && S_ISDIR(((t_file *)list->content)->mode) == 1)
		return (one_list(list, arg_list));
	while (list != NULL && S_ISDIR(((t_file *)list->content)->mode) == 0)
	{
		file = ((t_file *)list->content);
		if (file->error != 0)
			print_error(file->name, file->error);
		else if (S_ISDIR(file->mode) == 0)
			ft_putendl(file->name);
		list = list->next;
	}
	if (list != NULL)
	{
		ft_putchar('\n');
		return (base_list(list, arg_list));
	}
	return (0);
}

int			argv_to_list(char **argv, int argi, t_arg *arg_list)
{
	t_list	*tamp;
	t_list	*begin_list;
	t_file	file;

	if (get_stat(argv[argi--], &file) == 1)
		return (1);
	begin_list = ft_lstnew((void *)&file, sizeof(t_file));
	if (begin_list == NULL)
		return (1);
	while (argi > 0)
	{
		if (get_stat(argv[argi--], &file) == 1)
			return (1);
		tamp = ft_lstnew((void *)&file, sizeof(t_file));
		if (tamp == NULL)
			return (1);
		ft_lstadd(&begin_list, tamp);
		if (sort_list(&begin_list, arg_list) == 1)
			return (1);
		if (arg_list->arg[5] == 0 && sort_argv(&begin_list) == 1)
			return (1);
	}
	if (print_argv(begin_list, arg_list) == 1)
		return (1);
	return (0);
}
