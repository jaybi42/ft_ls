/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 19:10:05 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/05 16:39:35 by jguthert         ###   ########.fr       */
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

	gr = getgrgid(st_gid);
	if (gr != NULL)
		file->gp_id = gr->gr_name;
	pw = getpwuid(st_uid);
	if (pw != NULL)
		file->user_id = pw->pw_name;
}

static void		stat_dev(dev_t dev, t_file *file)
{
	file->minor = dev % 255;
	file->major = (dev >> 8) % 255;
}

static void		stat_time(t_file *file, time_t atime, time_t ctime, time_t mtime)
{

}

int			get_stat(char *path, t_file *file)
{
	int				ret_stat;
	struct stat		stat;

	ft_bzero(file, sizeof(t_file));
	file->path = ft_strdup(path);
	if (path != NULL)
		ft_strdel(&path);
	file->name = name_from_path(path);
	ret_stat = lstat(file->path, &stat);
	if (ret_stat == -1 && errno == 2)
	{
		file->is_fake = 1;
		return (0);
	}
	else if (ret_stat == -1)
		return (ERRORNO);
	stat_grpw(file, stat.st_gid, stat.st_uid);
	stat_time(file, stat.st_mtime, stat.st_ctime, stat.st_atime);
	stat_dev(stat.st_dev, file);
	file->mode = stat.st_mode;
	file->nb_link = stat.st_nlink;
	file->size = stat.st_size;
	file->ino = stat.st_ino;
		return (0);
}
