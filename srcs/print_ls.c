/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 18:52:50 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/14 14:57:04 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <unistd.h>
#include <errno.h>

static void		get_space(t_list *list)
{
	int		spaces[6] = {0, 0, 0, 0, 0, 0};
	int		ret;
	t_file	*file;

	while (list != NULL)
	{
		file = (t_file *)list->content;
		if ((ret = ft_nbrlen(file->ino)) > spaces[0])
			spaces[0] = ret;
		if((ret = ft_strlen(file->id.gp_id)) > spaces[1])
			spaces[1] = ret;
		if((ret = ft_strlen(file->id.user_id)) > spaces[2])
			spaces[2] = ret;
		if((ret = ft_nbrlen(file->id.ngp_id)) > spaces[3])
			spaces[3] = ret;
		if((ret = ft_nbrlen(file->id.nuser_id)) > spaces[4])
			spaces[4] = ret;
		if((ret = ft_nbrlen(file->size)) > spaces[5])
			spaces[5] = ret;
		list = list->next;
	}
}

static void		print_total(t_list *list)
{
	uint64_t size;

	size = 0;
	while (list != NULL)
	{
		size = size + (((t_file *)list->content)->size);
		list = list->next;
	}
	ft_putstr("total ");
	ft_putnbr(size / 512);
	ft_putchar('\n');
}

static void		print_name(char *path, char *name, bool is_lnk)
{
	char		buff[1024];
	ssize_t		len;

	if (name != NULL)
		ft_putstr(name);
	if (is_lnk == 1)
	{
		len = readlink(path, buff, sizeof(buff) - 1);
		if (len == -1)
			ERRORNO;
		ft_putstr(" -> ");
		buff[len] = '\0';
		ft_putstr(buff);
	}
	ft_putchar('\n');
}

void			print_ls(t_list *list, t_arg *arg_list)
{
	t_file	*file;

	if (list != NULL && arg_list->arg[9] == 1)
		print_total(list);
	while (list != NULL)
	{
		file = ((t_file *)list->content);
		if (file->error != 0)
		{
			print_error(file->name, file->error);
			list = list->next;
			continue ;
		}
		else if (arg_list->arg[8] == 1)
		{
			ft_putnbr(file->ino);
			ft_putchar(' ');
		}
		if (list != NULL && arg_list->arg[9] == 1)
			print_ls_ext(file, arg_list);
		print_name(file->path, file->name, S_ISLNK(file->mode));
		list = list->next;
	}
	ft_putchar('\n');
}
