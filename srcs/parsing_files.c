/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:12:17 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/23 23:53:14 by jguthert         ###   ########.fr       */
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

static t_file	*gen_info(char	*path)
{
	path = NULL;
	return (NULL);
}

static int		parse_l(t_file *file)
{
	if (get_stat(file) == 1)
		return (1);
	return (0);
}
/*
static int		get_files(char *path)
{
    DIR             *rep;
    struct dirent   *dir_info;
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
			file.namelen = dir_info->d_namlen;
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
	{
		file->is_fil = 1;
	}
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
		printf("list.content_size: [%i]\n", drive->content_size);
//		printf("name: [%s], is_dir: [%i], is_fil: [%i]\n", drive->file.name, drive->file.is_dir, drive->file.is_fil);
		drive = drive->next;
	}
}

t_list	*argv_to_list(char **argv, int max, int start, t_arg *arg_list)
{
	t_list			*list;
	t_list			*begin_list;
	t_file			file;

	if (check_file(argv[start++], &file) == 1)
		return (NULL);
//	printf("name_real: [%s], name_done: [%s], is_dir: [%i], is_fil: [%i]\n", argv[start - 1], file.name, file.is_dir, file.is_fil);
	begin_list = ft_lstnew(&file, sizeof(t_file));
	if (begin_list == NULL)
		return (NULL);
	while (start <= max)
	{
		if (check_file(argv[start++], &file) == 1)
			return (NULL);
		list = ft_lstnew(&file, sizeof(t_file));
		if (list == NULL)
			return (NULL);
		if (file.is_dir == 1)
			ft_lstadd_last(&begin_list, list);
		else if (file.is_fil == 0)
			ft_lstadd(&begin_list, list);
//		else
//			ft_lst_mid(&begin_list, list);
	}
	test_list(&begin_list);
//	sort_argv(&begin_list, arg_list);
	return (begin_list);
}
