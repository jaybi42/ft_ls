/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 17:42:49 by jguthert          #+#    #+#             */
/*   Updated: 2016/04/26 17:31:58 by jguthert         ###   ########.fr       */
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
	if (arg_list->arg[3] == 1 || arg_list->arg[5] == 1)
		return (1);
	if (arg_list->arg[0] == 1 && *str == '.' && str[1] != '.' && str[1] != '\0')
		return (1);
	if (str[0] == '.')
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

static int			make_list(char *path, t_arg *arg_list, t_list **new_list)
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
		if (add_list(new_path, arg_list, new_list) == 1)
			return (1);
	}
	if (closedir(dir) == -1)
		return (1);
	if (*new_list != NULL && (*new_list)->next != NULL)
		sort_list(new_list, arg_list);
	return (0);
}

static bool			get_realpath(t_file *f, int i, int j, bool alone)
{
	char	*new_path;
	int		len_path;
	int		len_lnk;

	if (alone == 1 && (f->name[0] == '.' && f->name[1] == '\0'))
		return (1);
	if (S_ISDIR(f->mode) == 1 && ((f->name[0] == '.' && f->name[1] == '\0') ||
								  (f->name[0] == '.' && f->name[1] == '.')))
		return (0);
	if (S_ISDIR(f->mode) == 1)
		return (1);
	if (f->lnk_isdir == 1)
	{
		len_path = ft_strlen(f->path) - ft_strlen(f->name);
		len_lnk = ft_strlen(f->lnk_path);
		new_path = ft_strnew(len_path + len_lnk);
		while (++i < len_path)
			new_path[i] = f->path[i];
		while (j < len_lnk)
			new_path[i++] = f->lnk_path[j++];
		ft_strdel(&f->lnk_path);
		f->lnk_path = new_path;
		return (1);
	}
	return (0);
}

int					base_list(t_list *list, t_arg *a_l, bool alone, bool first)
{
	t_list	*new_l;

	new_l = NULL;
	while (list != NULL)
	{
		if (get_realpath(((t_file *)list->content), -1, 0, alone) == 1)
		{
			if (make_list(((t_file *)list->content)->path, a_l, &new_l) == 1)
				return (1);
			if (alone == 0)
			{
				first == 1 ? first = 0 : ft_putchar('\n');
				ft_putstr(((t_file *)list->content)->path);
				ft_putendl(":");
			}
			print_ls(new_l, a_l);
			if (a_l->arg[1] == 1)
				base_list(new_l, a_l, 0, 0);
		}
		if (new_l != NULL)
			ft_lstdel(&new_l, free_list);
		list = list->next;
	}
	return (0);
}
