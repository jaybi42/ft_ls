/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 17:42:49 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/25 19:15:11 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

static int			can_add(char *str, t_arg *arg_list)
{
	if (str == NULL)
		return (0);
	if (arg_list->arg[4] == 1)
		return (1);
	else if (str[0] == '.' && arg_list->arg[0] == 0)
		return (0);
	else if (str[0] == '.' && str[1] == '.' &&
			 (arg_list->arg[0] == 0 || arg_list->arg[5] == 0))
		return (0);
	return (1);
}

static char			*make_path(char *path, char *name)
{
	char	*new_path;
	char	*tamp;

	if (path == NULL || name == NULL)
		return (NULL);
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

int				add_list(char *path, t_list **new_list)
{
	t_list		*tamp;
	t_file		file;

	if (*new_list == NULL)
	{
		get_stat(path, &file);
		*new_list = ft_lstnew((void *)&file, sizeof(t_file));
		if (*new_list == NULL)
			return (1);
	}
	else
	{
		get_stat(path, &file);
		tamp = ft_lstnew((void *)&file, sizeof(t_file));
		if (tamp == NULL)
			return (1);
		ft_lstadd(new_list, tamp);
	}
	return (0);
}

static int				make_list(char *path, t_arg *arg_list, t_list **new_list)
{
	DIR				*dir;
	char			*new_path;
	struct dirent	*st_dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		print_error(path, errno);
		return (0);
	}
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
		return (1);
	if (*new_list != NULL && (*new_list)->next != NULL)
		sort_list(new_list, arg_list);
	return (0);
}

static bool		get_realpath(char **path, t_file *file)
{
	if (file->lnk_path != NULL)
	{
		*path = file->lnk_path;
		return (1);
	}
	if (S_ISDIR(file->mode) == 1)
	{
		*path = file->path;
		return (1);
	}
	return (0);
}

int				base_list(t_list *list, t_arg *a_l, bool alone, bool first)
{
	t_list	*link;
	t_list	*new_l;
	char	*path;

	path = NULL;
	link = list;
	new_l = NULL;
	while (link != NULL)
	{
		if (get_realpath(&path, ((t_file *)link->content)) == 1)
		{
			if (make_list(path, a_l, &new_l) == 1)
				return (1);
			if (alone == 0)
			{
				first == 1 ? first = 0 : ft_putchar('\n');
				ft_putstr(((t_file *)link->content)->path);
				ft_putendl(":");
			}
			print_ls(new_l, a_l);
			if (a_l->arg[1] == 1)
				base_list(new_l, a_l, 0, 0);
		}
		if (new_l != NULL)
			ft_lstdel(&new_l, free_list);
		link = link->next;
	}
	return (0);
}
