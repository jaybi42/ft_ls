/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 19:10:05 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/19 20:27:47 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int			get_stat(t_file *file)
{
	int				ret_stat;
	struct stat		stat;
	struct group	*gr;
	struct passwd	*pw;

	ret_stat = 0;
	ret_stat = lstat(file->path, &stat);
	if (ret_stat == -1)
		return (ERRORNO);
	gr = getgrgid(stat.st_gid);
	file->gp_id = gr->gr_name;
	pw = getpwuid(stat.st_uid);
	file->user_id = pw->pw_name;
	file->mode = stat.st_mode;
	file->nb_link = stat.st_nlink;
	file->size = stat.st_size;
	return (0);
}
