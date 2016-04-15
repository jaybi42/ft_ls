/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:27:30 by jguthert          #+#    #+#             */
/*   Updated: 2016/04/13 15:26:31 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

int				add_list(char *path, t_arg *arg_list, t_list **new_list)
{
	t_list		*tamp;
	t_file		file;

	if (*new_list == NULL)
	{
		get_stat(path, &file, arg_list);
		*new_list = ft_lstnew((void *)&file, sizeof(t_file));
		if (*new_list == NULL)
			return (1);
	}
	else
	{
		get_stat(path, &file, arg_list);
		tamp = ft_lstnew((void *)&file, sizeof(t_file));
		if (tamp == NULL)
			return (1);
		ft_lstadd_last(new_list, tamp);
	}
	return (0);
}

void			free_list(void *content, size_t size)
{
	t_file	*file;
	char	*path;
	char	*lnk;

	(void)size;
	file = (t_file *)content;
	if (file != NULL)
	{
		path = (char *)file->path;
		lnk = (char *)file->lnk_path;
		if (path != NULL)
			ft_strdel(&path);
		if (lnk != NULL)
			ft_strdel(&lnk);
		free(content);
		content = NULL;
	}
}
