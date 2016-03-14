/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 18:52:50 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/14 17:58:59 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <unistd.h>
#include <errno.h>

static void		get_maxlen(bool n, t_list *list, t_maxlen *maxlen)
{
	t_file	*file;

	ft_bzero(maxlen, sizeof(t_maxlen));
	while (list != NULL)
	{
		file = (t_file *)list->content;
		if ((n == 1 || file->id.gp == NULL) && maxlen->gp < file->id.gp_len)
			maxlen->gp = ft_nbrlen(file->id.ngp);
		else if (n == 0 && maxlen->gp < ft_nbrlen(file->id.ngp))
			maxlen->gp = file->id.gp_len;
		if ((n == 1 || file->id.user == NULL) && maxlen->user < file->id.user_len)
			maxlen->user = ft_nbrlen(file->id.nuser);
		else if (n == 0 && maxlen->user < ft_nbrlen(file->id.nuser))
			maxlen->user = file->id.user_len;
		if (maxlen->ino < ft_nbrlen(file->ino))
			maxlen->ino = ft_nbrlen(file->ino);
		if (maxlen->size < ft_nbrlen(file->size))
			maxlen->size = ft_nbrlen(file->size);
		if (maxlen->nb_link < ft_nbrlen(file->nb_link))
			maxlen->nb_link = ft_nbrlen(file->nb_link);
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

static void		print_ino(int ino, int ino_maxlen)
{
	int i;

	i = ino_maxlen - ft_nbrlen(ino);
	ft_putnbr(ino);
	while (i-- > 0)
		ft_putchar(' ');
	ft_putchar(' ');
}

void			print_ls(t_list *list, t_arg *arg_list)
{
	t_file		*file;
	t_maxlen	maxlen;

	get_maxlen(arg_list->arg[10], list, &maxlen);
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
			print_ino(file->ino, maxlen.ino);
		if (list != NULL && arg_list->arg[9] == 1)
			print_ls_ext(file, arg_list, &maxlen);
		print_name(file->path, file->name, S_ISLNK(file->mode));
		list = list->next;
	}
	ft_putchar('\n');
}
