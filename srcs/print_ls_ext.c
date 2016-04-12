/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 18:02:25 by jguthert          #+#    #+#             */
/*   Updated: 2016/04/12 18:35:54 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/xattr.h>
#include <sys/acl.h>

static void		print_size(uint64_t size, bool h, t_maxlen *maxlen)
{
	char const	base[] = "BKMGTPE";
	int			i;
	int			len;

	if (h == 1)
	{
		i = ft_nbrlen(size) / 3;
		len = 5 - ft_nbrlen(size / ft_power(1000, i));
		i != 0 ? len -= 2 : len;
		while (len-- > 0)
			ft_putchar(' ');
		ft_putnbr(size / ft_power(1000, i));
		if (i != 0)
			ft_putchar('.');
		if (i != 0)
			ft_putnbr((size % ft_power(1000, i)) / 100);
		i <= 6 ? ft_putchar(base[i]) : ft_putchar(base[6]);
	}
	else
	{
		i = maxlen->size - ft_nbrlen(size);
		while (i-- > 0)
			ft_putchar(' ');
		ft_putnbr(size);
	}
}

static void		print_id(t_file *file, bool g, bool n, t_maxlen *maxlen)
{
	int		i;

	if (g == 0)
	{
		if (n == 1 || file->id.user == NULL)
			ft_putnbr(file->id.nuser);
		else
			ft_putstr(file->id.user);
		if (n == 1 || file->id.user == NULL)
			i = maxlen->user - ft_nbrlen(file->id.nuser) + 2;
		else
			i = maxlen->user - ft_strlen(file->id.user) + 2;
		while (i-- > 0)
			ft_putchar(' ');
	}
	if (n == 1 || file->id.gp == NULL)
		ft_putnbr(file->id.ngp);
	else
		ft_putstr(file->id.gp);
	if (n == 1 || file->id.gp == NULL)
		i = maxlen->gp - ft_nbrlen(file->id.ngp) + 2;
	else
		i = maxlen->gp - ft_strlen(file->id.gp) + 2;
	while (i-- > 0)
		ft_putchar(' ');
}

static int		print_mode(uint16_t mode, char *path)
{
	char const	base[] = "-rwxrwxrwx";
	char const	type[] = "-pc-d-b---l-s----";
	int			i;
	acl_t		acl;

	i = 1;
	acl = NULL;
	ft_putchar(type[((mode >> 12) > 16 ? 0 : mode >> 12)]);
	while (i < 10)
	{
		if ((mode >> (9 - i)) & 1)
			ft_putchar(base[i]);
		else
			ft_putchar('-');
		i++;
	}
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 1)
		ft_putchar('@');
	else if (acl_get_file(path, ACL_TYPE_EXTENDED))
		ft_putchar('+');
	else
		ft_putchar(' ');
	ft_putstr(" ");
	acl_free((void *)acl);
	return (0);
}

static void		print_majmin(int major, int minor, t_maxlen *maxlen)
{
	int		i;

	i = maxlen->major - ft_nbrlen(major) + 1;
	while (i-- > 0)
		ft_putchar(' ');
	ft_putnbr(major);
	ft_putstr(", ");
	i = maxlen->minor - ft_nbrlen(minor) + 1;
	while (i-- > 0)
		ft_putchar(' ');
	ft_putnbr(minor);
	ft_putchar(' ');
}

void			print_ls_ext(t_file *file, t_arg *arg_list, t_maxlen *maxlen)
{
	int		i;

	i = maxlen->nb_link - ft_nbrlen(file->nb_link);
	print_mode(file->mode, file->path);
	while (i-- > 0)
		ft_putchar(' ');
	ft_putnbr(file->nb_link);
	ft_putchar(' ');
	print_id(file, arg_list->arg[6], arg_list->arg[10], maxlen);
	if (S_ISCHR(file->mode) == 1 || S_ISBLK(file->mode) == 1)
		print_majmin(file->major, file->minor, maxlen);
	else
	{
		print_size(file->size, arg_list->arg[7], maxlen);
		ft_putchar(' ');
	}
	print_time(file->time);
}
