/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 19:10:05 by jguthert          #+#    #+#             */
/*   Updated: 2016/04/13 15:24:03 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

static char			*name_from_path(char *path)
{
	int	max;

	max = ft_strlen(path);
	while (path[max] != '/' && max > 0)
		max--;
	if (path[max] == '/')
		max++;
	return (&path[max]);
}

static void			stat_grpw(t_file *file, gid_t st_gid, uid_t st_uid)
{
	struct group	*gr;
	struct passwd	*pw;

	ft_bzero(&(file->id), sizeof(t_id));
	gr = getgrgid(st_gid);
	if (gr != NULL)
	{
		file->id.gp = gr->gr_name;
		file->id.gp_len = ft_strlen(gr->gr_name);
	}
	file->id.ngp = st_gid;
	pw = getpwuid(st_uid);
	if (pw != NULL)
	{
		file->id.user = pw->pw_name;
		file->id.user_len = ft_strlen(pw->pw_name);
	}
	file->id.nuser = st_uid;
}

static void			stat_time(t_file *file, struct stat stat, t_arg *arg_list)
{
	if (arg_list->arg[4] == 1)
	{
		file->time = stat.st_ctimespec.tv_sec;
		file->nano = stat.st_ctimespec.tv_nsec;
	}
	else if (arg_list->arg[13] == 1)
	{
		file->time = stat.st_atimespec.tv_sec;
		file->nano = stat.st_atimespec.tv_nsec;
	}
	file->time = stat.st_mtimespec.tv_sec;
	file->nano = stat.st_mtimespec.tv_nsec;
}

static void			lnk_isdir(t_file *file, bool l_opt)
{
	char		buff[1024];
	ssize_t		len;
	struct stat	get_stat;

	if (S_ISLNK(file->mode) == 0)
		return ;
	len = readlink(file->path, buff, sizeof(buff) - 1);
	if (len == -1)
		return ;
	buff[len] = '\0';
	file->lnk_path = ft_strdup(buff);
	if (stat(file->path, &get_stat) == -1)
		return ;
	if (S_ISDIR(get_stat.st_mode) == 1 && l_opt == 0)
		file->lnk_isdir = 1;
}

int					get_stat(char *path, t_file *file, t_arg *arg_list)
{
	int			ret_stat;
	struct stat	stat;

	ft_bzero(file, sizeof(t_file));
	file->path = ft_strdup(path);
	if (file->path == NULL)
		return (1);
	file->name = name_from_path(path);
	ret_stat = lstat(file->path, &stat);
	if (ret_stat == -1)
	{
		file->error = errno;
		return (1);
	}
	stat_grpw(file, stat.st_gid, stat.st_uid);
	stat_time(file, stat, arg_list);
	file->minor = minor(stat.st_rdev);
	file->major = major(stat.st_rdev);
	file->mode = stat.st_mode;
	file->nb_link = stat.st_nlink;
	file->size = stat.st_size;
	file->ino = stat.st_ino;
	file->blocks = stat.st_blocks;
	lnk_isdir(file, arg_list->arg[9]);
	return (0);
}
