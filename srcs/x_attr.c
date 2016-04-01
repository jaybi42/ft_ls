/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_attr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 01:57:44 by jguthert          #+#    #+#             */
/*   Updated: 2016/04/01 03:31:12 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/xattr.h>

int				x_attr(t_file *file)
{
	char const	base[] = " .+@";
	int			i;
	ssize_t		ret_list;
//	ssize_t		ret_get;

	i = 0;
	ret_list = listxattr(file->path, file->name, file->size, XATTR_NOFOLLOW);
//	ret_get = getxattr(file->path, file->name, );
	file->acl = base[i];
	return (0);
}
