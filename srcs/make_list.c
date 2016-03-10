/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 17:42:49 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/10 16:47:26 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

static int			can_add(char *str, t_arg *arg_list)
{
	if (arg_list->arg[4] == 1)
		return (1);
	else if (str[0] == '.' && arg_list->arg[0] == 0)
		return (0);
	else if (str[0] == '.' && str[1] == '.' && arg_list->arg[0] == 0)
		return (0);
	return (1);
}

static char			*make_path(char *path, char *name)
{
	char	*new_path;
	char	*tamp;

	if (path[ft_strlen(path) - 1] != '/')
	{
		tamp = ft_strjoin(path, "/");
		if (tamp == NULL)
			return (NULL);
		new_path = ft_strjoin(tamp, name);
		ft_strdel(&tamp);
	}
	else
		new_path = ft_strjoin(path, name);
	if (new_path == NULL)
		return (NULL);
	return (new_path);
}

static int			add_list(char *path, t_list **new_list)
{
	t_list			*tamp;
	t_file			file;

	if (*new_list == NULL)
	{
		if (get_stat(path, &file) == 1)
			return (1);
		*new_list = ft_lstnew((void *)&file, sizeof(t_file));
		if (*new_list == NULL)
			return (ERROR);
	}
	else
	{
		if (get_stat(path, &file) == 1)
			return (1);
		tamp = ft_lstnew((void *)&file, sizeof(t_file));
		if (tamp == NULL)
			return (ERROR);
		ft_lstadd(new_list, tamp);
	}
	return (0);
}

static int			make_list(char *path, t_arg *arg_list, t_list **new_list)
{
	DIR				*dir;
	char			*new_path;
	struct dirent	*st_dir;

	dir = opendir(path);
	if (dir == NULL)
		return (ERRORNO);
	while (dir != NULL && (st_dir = readdir(dir)) != NULL)
	{
		if (can_add(st_dir->d_name, arg_list) == 0)
			continue ;
		new_path = make_path(path, st_dir->d_name);
		if (new_path == NULL)
			return (1);
		if (add_list(new_path, new_list) == 1)
			return (1);
	}
	if (closedir(dir) == -1)
		return (ERRORNO);
	return (0);
}

int				base_list(t_list *list, t_arg *arg_list)
{
	t_list	*link;
	t_list	*new_list;
	int		ret;

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
			ft_putstr(((t_file *)link->content)->path);
			ft_putendl(":");
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
