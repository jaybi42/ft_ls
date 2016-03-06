/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 18:52:50 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/06 19:19:30 by jguthert         ###   ########.fr       */
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
	uint64_t	comma;

	comma = size;
	i = 0;
	if (h == 1)
	{
		while (size > 1000)
		{
			size /= 1000;
			if (i != 0)
				comma /= 1000;
			i++;
		}
		ft_putnbr(size);
		if (i != 0)
		{
			ft_putchar('.');
			ft_putnbr((comma % 1000) / 100);
		}
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
		if (n == 1 || file->id.user_id == NULL)
			ft_putnbr(file->id.nuser_id);
		else
			ft_putstr(file->id.user_id);
	}
	ft_putstr("  ");
	if (n == 1 || file->id.user_id == NULL)
		ft_putnbr(file->id.ngp_id);
	else
		ft_putstr(file->id.gp_id);
	ft_putstr("  ");
}

static int		print_mode(uint16_t mode)
{
	char const	base[] = "-rwxrwxrwx";
	char const	type[] = "-pc-d-b---l-s----";
	int			i;

	i = 1;
	ft_putchar(type[((mode >> 12) > 16 ? 0 : mode >> 12)]);
	while (i < 10)
	{
		if ((mode >> (9 - i)) & 1)
			ft_putchar(base[i]);
		else
			ft_putchar('-');
		i++;
	}
	ft_putstr("  ");
	return (0);
}

static void		print_ino(int ino, bool h)
{
	if (h == 1)
	{
		ft_putnbr(ino);
		ft_putchar(' ');
	}
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
		print_ino(file->ino, arg_list->arg[8]);
		if (list != NULL && arg_list->arg[9] == 1)
		{
			print_mode(file->mode);
			print_nlink(file->nb_link);
			print_ID(file, arg_list->arg[6], arg_list->arg[10]);
			print_size(file->size, arg_list->arg[7]);
			if (arg_list->arg[13] == 1)
				print_time(file->time.mtime);
			else if (arg_list->arg[3] == 1)
				print_time(file->time.atime);
			else
				print_time(file->time.ctime);
		}
		print_name(file->path, file->name, S_ISLNK(file->mode));
		list = list->next;
	}
}
