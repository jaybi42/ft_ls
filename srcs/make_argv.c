/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:12:17 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/03 21:59:52 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

static char		*name_from_path(char *path)
{
	int		max;

	max = ft_strlen(path);
	while (path[max] != '/' && max > 0)
		max--;
	if (path[max] == '/')
		max++;
	return (&path[max]);
}

/*int				check_file(char *path, t_file *file)
{
	DIR		*dir;

	ft_bzero(file, sizeof(t_file));
	dir = opendir(path);
	file->path = path;
	file->name = name_from_path(path);
	if (dir == NULL && errno != 20)
		file->is_fake = 1;
	else if (dir != NULL)
	{
		file->is_dir = 1;
		get_stat(file);
	}
	else
		get_stat(file);
	if (dir != NULL && closedir(dir) == -1)
		return (ERRORNO);
	return (0);
	}*/

int			check_file(char *path, t_file *file)
{
	ft_bzero(file, sizeof(t_file));
	file->path = path;
	file->name = name_from_path(path);
	if (get_stat(file) == 1)
	{
		if (errno == 2)
		{
			file->is_fake = 1;
			return (0);
		}
		return (1);
	}
	if (S_ISDIR(file->mode) == 1)
		file->is_dir = 1;
	return (0);
}

static void test_list(t_list **begin_list)
{
	t_list *drive;

	drive = *begin_list;
	while (drive != NULL)
	{
		if (((t_file *)drive->content)->is_dir == 1)
			printf("\n%s:\n", ((t_file *)drive->content)->name);
		else
			printf("%s\n", ((t_file *)drive->content)->name);
		drive = drive->next;
	}
	printf("----------------------\n");
}

int			argv_to_list(char **argv, int argi, t_arg *arg_list)
{
	t_list	*tamp;
	t_list	*begin_list;
	t_file	file;

	if (check_file(argv[argi--], &file) == 1)
		return (1);
	begin_list = ft_lstnew(&file, sizeof(t_file));
	if (begin_list == NULL)
		return (1);
	while (argi > 0)
	{
		if (check_file(argv[argi--], &file) == 1)
			return (1);
		tamp = ft_lstnew(&file, sizeof(t_file));
		if (tamp == NULL)
			return (1);
		ft_lstadd(&begin_list, tamp);
	}
	if (sort_list(&begin_list, arg_list) == 1)
		return (1);
	if (arg_list->arg[5] == 0 && sort_argv(&begin_list) == 1)
		return (1);
	base_list(begin_list, arg_list);
	return (0);
}
