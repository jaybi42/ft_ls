/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:12:17 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/24 23:46:43 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

static void aff_error(char *name)
{
	ft_putstr("ls: ");
	ft_putstr(name);
	ft_putstr(": ");
	ft_putendl(strerror(errno));
}

/*
static int		get_files(char *path)
{
    DIR             *rep;
    t_file          file;

	file = FILE_INIT;
	file.path = path;
    rep = opendir(path);
	if (rep == NULL && errno != 20)
		return (ERRORNO);
	else if (rep == NULL && errno == 20)
		info_file()
	else
	{
		while ((dir_stat = readdir(rep)) != NULL)
		{
			if (dir_info->d_name[0] != '.')
				printf("%s\n", dir_info->d_name);
			file.name = dir_info->d_name;
			file.is_dir = 1;
		}
		if (closedir(rep))
			return (ERRORNO);
	}
	return (0);
}
*/

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
	DIR             *rep;

	*file = FILE_INIT;
	rep = opendir(path);
	file->path = path;
	file->name = name_from_path(path);
	if (rep == NULL && errno == 20)
		file->is_fil = 1;
	else if (rep != NULL)
	{
		file->is_dir = 1;
		if (closedir(rep))
			return (ERRORNO);
	}
	return (0);
}


static void test_list(t_list **begin_list)
{
	t_list *drive;

	drive = *begin_list;
	while (drive != NULL)
	{
		printf("name: [%s]\n", ((t_file *)drive->content)->name);
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
	test_list(&begin_list);
	return (0);
}
