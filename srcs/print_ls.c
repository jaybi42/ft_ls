/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 18:52:50 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/04 20:10:27 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>
#include <string.h>

static void		print_error(char *name)
{
	if (name == NULL)
		return ;
	ft_putstr("ls: ");
	ft_putstr(name);
	ft_putstr(": ");
	ft_putendl("No such file or directory");
}



static void		print_size(uint64_t size, bool h)
{
	char const	base[] = "bKMG";
	int			i;

	i = 0;
	if (h == 1)
	{
		while (size > 1000)
		{
			size /= 1000;
			i++;
		}
		ft_putnbr(size);
		ft_putchar(base[i]);
	}
	else
		ft_putnbr(size);
	ft_putstr(" ");
}

static void		print_ID(t_file *file, bool g, bool n)
{
	if (g == 0)
	{
		if (n == 1 || file->user_id == NULL)
			ft_putnbr(file->nuser_id);
		else
			ft_putstr(file->user_id);
	}
	ft_putstr(" ");
	if (n == 1 || file->user_id == NULL)
		ft_putnbr(file->ngp_id);
	else
		ft_putstr(file->gp_id);
	ft_putstr(" ");
}

static int		print_mode(uint16_t mode, int ino, bool h)
{
	char const	base[] = "rwxrwxrwx";
	char const	type[] = "-pc-d-b---l-s----";
	int			i;

	i = 9;
	if (h == 1)
	{
		ft_putnbr(ino);
		return (0);
	}
	ft_putchar(type[((mode >> 12) > 16 ? 0 : mode >> 12)]);
	while (i > 0)
	{
		if ((mode >> i) & 1)
			ft_putchar(base[i]);
		else
			ft_putchar('-');
		i--;
	}
	ft_putstr(" ");
	return (0);
}

void			print_ls(t_list *list, t_arg *arg_list)
{
	t_file	*file;

	if (list != NULL && arg_list->arg[9] == 1)
		print_total(list);
	while (list != NULL)
	{
		file = ((t_file *)list->content);
		if (file->is_fake == 1)
		{
			print_error(file->name);
			list = list->next;
			continue ;
		}
		else if (list != NULL && arg_list->arg[9] == 1)
		{
			print_mode(file->mode, file->ino, arg_list->arg[8]);
			print_nlink(file->nb_link);
			print_ID(file, arg_list->arg[6], arg_list->arg[10]);
			print_size(file->size, arg_list->arg[7]);
			if (arg_list->arg[13] == 1)
				print_time(file->atime);
			else if (arg_list->arg[3] == 1)
				print_time(file->ctime);
			else
				print_time(file->mtime);
		}
		print_name(file->name, S_ISLNK(file->mode));
		list = list->next;
	}
}
