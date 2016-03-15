/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:12:17 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/15 21:49:09 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

void		free_list(void *content, size_t size)
{
	(void)size;
	if (content != NULL)
	{
		if (((t_file *)content)->path != NULL)
			ft_strdel(&((t_file *)content)->path);
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
                print_error(((t_file *)link->content)->name,
                            ((t_file *)link->content)->error);
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
	int		ret;

	file = (t_file *)list->content;
	if (list->next == NULL && S_ISDIR(((t_file *)list->content)->mode) == 1)
	{
		ret = one_list(list, arg_list);
			return (ret);
	}
	while (list != NULL && file->error != 0)
	{
		file = (t_file *)list->content;
		print_error(file->name, file->error);
		list = list->next;
	}
	ret = base_list(list, arg_list);
	return (ret);
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
