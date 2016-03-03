/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 18:00:58 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/03 19:00:25 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <dirent.h>

static int	arg_error(char c, const char *base)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ls [-", 2);
	ft_putstr_fd(base, 2);
	ft_putendl_fd("] [file ...]", 2);
	return (1);
}

static int	is_in(char c, const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	get_flag(int argc, char **argv, t_arg *arg_list)
{
	char const	base[] = "ARSUafghilnrtu";
	char		*tmp;
	int			i;
	int			ret;

	i = 1;
	while (i < argc)
	{
		tmp = argv[i];
		if (*tmp != '-')
			return (0);
		tmp++;
		while (*tmp)
		{
			ret = is_in(*tmp, base);
			if (ret >= 0)
				arg_list->arg[ret] = 1;
			else
				return (arg_error(*tmp, base));
			tmp++;
		}
		i++;
	}
	return (0);
}

static int	make_ls(int argc, char **argv, t_arg *arg_list)
{
	char	*root[] = {".", NULL};
	int		ret;

	argc -= 1;
	while (argc > 0 && argv[1][0] == '-')
	{
		argv++;
		argc--;
	}
	if (argc == 0)
		ret = argv_to_list(root, 0, arg_list);
	else
		ret = argv_to_list(argv, argc, arg_list);
	return (ret);
}

int			main(int argc, char **argv)
{
	t_arg	arg_list;

	arg_list = ARG_INIT;
	if (get_flag(argc, argv, &arg_list) == 1)
		return (1);
	else if (make_ls(argc, argv, &arg_list) == 1)
		return (1);
	return (0);
}
