/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 18:52:50 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/25 18:39:08 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <unistd.h>
#include <errno.h>

static void		get_maxlen(bool n, t_list *list, t_maxlen *ml)
{
	t_file	*f;

	while (list != NULL)
	{
		f = (t_file *)list->content;
		if ((n == 1 || f->id.gp == NULL) && ml->gp < ft_nbrlen(f->id.ngp))
			ml->gp = ft_nbrlen(f->id.ngp);
		else if (n == 0 && ml->gp < f->id.gp_len)
			ml->gp = f->id.gp_len;
		if ((n == 1 || f->id.user == NULL) && ml->user < ft_nbrlen(f->id.nuser))
			ml->user = ft_nbrlen(f->id.nuser);
		else if (n == 0 && ml->user < f->id.user_len)
			ml->user = f->id.user_len;
		if (ml->ino < ft_nbrlen(f->ino))
			ml->ino = ft_nbrlen(f->ino);
		if (ml->size < ft_nbrlen(f->size))
			ml->size = ft_nbrlen(f->size);
		if (ml->nb_link < ft_nbrlen(f->nb_link))
			ml->nb_link = ft_nbrlen(f->nb_link);
		if (ml->major < ft_nbrlen(f->major))
			ml->major = ft_nbrlen(f->major);
		if (ml->minor < ft_nbrlen(f->minor))
			ml->minor = ft_nbrlen(f->minor);
		list = list->next;
	}
}

static void		print_total(t_list *list)
{
	uint64_t size;

	size = 0;
	while (list != NULL)
	{
		size = size + (((t_file *)list->content)->blocks);
		list = list->next;
	}
	ft_putstr("total ");
	ft_putnbr(size);
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
			return ;
		ft_putstr(" -> ");
		buff[len] = '\0';
		ft_putstr(buff);
	}
	ft_putchar('\n');
}

static void		print_ino(int ino, int ino_maxlen)
{
	int i;

	i = ino_maxlen - ft_nbrlen(ino) + 1;
	while (i-- > 0)
		ft_putchar(' ');
	ft_putnbr(ino);
	ft_putchar(' ');
}

void			print_ls(t_list *list, t_arg *arg_list)
{
	t_file		*file;
	t_maxlen	maxlen;

	ft_bzero(&maxlen, sizeof(t_maxlen));
	get_maxlen(arg_list->arg[10], list, &maxlen);
	if (list != NULL && arg_list->arg[9] == 1 &&
		S_ISDIR(((t_file *)list->content)->mode) == 1)
		print_total(list);
	while (list != NULL)
	{
		file = ((t_file *)list->content);
		if (arg_list->arg[8] == 1)
			print_ino(file->ino, maxlen.ino);
		if (list != NULL && arg_list->arg[9] == 1)
			print_ls_ext(file, arg_list, &maxlen);
		print_name(file->path, file->name, S_ISLNK(file->mode));
		list = list->next;
	}
}
