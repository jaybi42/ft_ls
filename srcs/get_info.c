/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 19:10:05 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/15 21:40:24 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

static char		*name_from_path(char *path)
{
	int	max;

	max = ft_strlen(path);
	while (path[max] != '/' && max > 0)
		max--;
	if (path[max] == '/')
		max++;
	return (&path[max]);
}

static void		stat_grpw(t_file *file, gid_t st_gid, uid_t st_uid)
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

static void		stat_time(t_file *file, struct timespec atime,
						  struct timespec ctime, struct timespec mtime)
{
	ft_bzero(&(file->time), sizeof(t_time));
	file->time.atime = atime.tv_sec;
	file->time.anano = atime.tv_nsec;
	file->time.ctime = ctime.tv_sec;
	file->time.cnano = ctime.tv_nsec;
	file->time.mtime = mtime.tv_sec;
	file->time.mnano = mtime.tv_nsec;
}

int			get_stat(char *path, t_file *file)
{
	int				ret_stat;
	struct stat		stat;

	ft_bzero(file, sizeof(t_file));
	file->path = path;
	file->name = name_from_path(path);
	ret_stat = lstat(file->path, &stat);
	if (ret_stat == -1)
	{
		file->error = errno;
		return (0);
	}
	stat_grpw(file, stat.st_gid, stat.st_uid);
	stat_time(file, stat.st_mtimespec, stat.st_ctimespec, stat.st_atimespec);
	file->minor = minor(stat.st_rdev);
	file->major = major(stat.st_rdev);
	file->mode = stat.st_mode;
	file->nb_link = stat.st_nlink;
	file->size = stat.st_size;
	file->ino = stat.st_ino;
	file->blocks = stat.st_blocks;
		return (0);
}
