/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 17:42:49 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/02 18:31:55 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int      check_file(char *path, t_file *file, t_arg *arg_list)
{
    DIR             *dir;
	struct dirent	*st_dir;

    ft_bzero(file, sizeof(t_file));
    dir = opendir(path);
    if (dir == NULL && errno != 20)
        file->is_fake = 1;
    else if (dir != NULL)
    {
		while ((st_dir = readdir(dir)) != NULL)
		{
			if (st_dir->d_name[0] == '.' && )
				printf("%s\n", st_dir->d_name);
			file->name = st_dir->d_name;
			file->is_dir = 1;
			get_stat(file);
		}
		if (closedir(dir))
			return (ERRORNO);
	}
    else
        get_stat(file);
    return (0);
}

static int		can_add(char *str)
{
	if (str[0] == '.' && arg_list[0] == 1)
		return (0);
	else if (str[0] == '.' && str[1] == '.' && arg_list[0] == 1)
		return (0);
	while(*str)
		str++;
	if (*(str - 1) == '~' && arg_list[0] == 1)
		return (0);
	return (1);
}

static int		add_list(t_list **new_list)
{
	t_file			file;

	while (argi > 0)
	{

	}
}

static int		make_list(char *path, t_file *file, t_arg *arg_list, t_list **new_list)
{
	t_list			*tamp;
	DIR				*dir;
	struct dirent	*st_dir;

	ft_bzero(file, sizeof(t_file));
	dir = opendir(path);
	file->path = path;
	while (dir != NULL && (st_dir = readdir(dir)) != NULL)
	{
		if (can_add(st_dir->d_name, arg_list) == 0)
			continue ;

		file->name = st_dir->d_name;
		if (*new_list == NULL)
		{
			*new_list = ft_lstnew(&file, sizeof(t_file));
			if (*new_list == NULL)
				return (ERROR);
		}
		else
		{
			tamp = ft_lstnew(&file, sizeof(t_file));
			if (tamp == NULL)
				return (ERROR);
			ft_lstadd(&begin_list, tamp);
		}
	}
	get_stat(file);
	return (0);
}

int				base_list(t_list *list, t_arg *arg_list)
{
	t_list	*link;
	t_list	*new_list;
	t_file	*file;

	print_ls(list, arg_list);
	link = list;
	new_list = NULL;
	while (link != NULL)
	{
		if (((t_file *)link->content)->is_dir == 1)
		{
			make_list(((t_file *)link->content)->path, file, arg_list, &new_list);
			sort_list(&new_list, arg_list);
			if (arg->arg_list[0] == 1)
				base_list(new_list, arg_list);
			else
				print_ls(new_list, arg_list);
		}
		link = link->next;
	}
	if (new_list != NULL)
		ft_lstdel(new_list);
	return (0);
}
