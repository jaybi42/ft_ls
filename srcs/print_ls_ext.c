/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 18:02:25 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/10 18:53:37 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <string.h>

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
	ft_putstr("	");
	if (n == 1 || file->id.user_id == NULL)
		ft_putnbr(file->id.ngp_id);
	else
		ft_putstr(file->id.gp_id);
	ft_putstr("	");
}

static int		print_mode(uint16_t mode)
{
	char const	base[] = "-rwxrwxrwx";
	char const	type[] = "-pc-d-b---l-s----";
	int		i;

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
	ft_putstr("	");
	return (0);
}

void	print_error(char *name, int error)
{
	if (name == NULL)
		return ;
	ft_putstr("ls: ");
	ft_putstr(name);
	ft_putstr(": ");
	ft_putendl(strerror(error));
}

void	print_ls_ext(t_file *file, t_arg *arg_list)
{
	print_mode(file->mode);
	ft_putnbr(file->nb_link);
	ft_putstr(" ");
	print_ID(file, arg_list->arg[6], arg_list->arg[10]);
	print_size(file->size, arg_list->arg[7]);
	if (arg_list->arg[13] == 1)
		print_time(file->time.mtime);
	else if (arg_list->arg[3] == 1)
		print_time(file->time.atime);
	else
		print_time(file->time.ctime);
}
