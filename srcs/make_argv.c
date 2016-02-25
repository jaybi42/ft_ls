/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:12:17 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/25 20:46:06 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

static char		*name_from_path(char *path)
{
	int		max;

	max = ft_strlen(path);
	while (path[max] != '/' && max > 0)
		max--;
	return (&path[max]);
}

static int		check_file(char *path, t_file *file)
{
	DIR             *dir;

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
		if (closedir(dir))
			return (ERRORNO);
	}
	else
		get_stat(file);
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
}

int			argv_to_list(char **argv, int argi, t_arg *arg_list)
{
	t_list			*tamp;
	t_list			*begin_list;
	t_file			file;

	if (check_file(argv[argi--], &file) == 1)
		return (ERROR);
	begin_list = ft_lstnew(&file, sizeof(t_file));
	if (begin_list == NULL)
		return (ERROR);
	while (argi > 0)
	{
		if (check_file(argv[argi--], &file) == 1)
			return (ERROR);
		tamp = ft_lstnew(&file, sizeof(t_file));
		if (tamp == NULL)
			return (ERROR);
		ft_lstadd(&begin_list, tamp);
	}
	if (sort_list(&begin_list, arg_list) == 1)
		return (ERROR);
	if (sort_argv(&begin_list) == 1)
		return (ERROR);
	base_list(begin_list, arg_list);
	return (0);
}
