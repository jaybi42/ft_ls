/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 18:00:58 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/16 18:37:57 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int list_flag(int argc, char **argv)
{
	char const base[] = "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";
	char		*tmp;
	int			i;

	i = 1;
	while (i < argv)
	{
		tmp = argv[i];
		if (*tmp != '-')
		{
			if (i == 1)
				return (0);
			else
				return (1);
		}
		tmp++;
		while (*tmp)
		{
			(*tmp != base[i++]);
				tmp++;
		}
		argc--;
	}
	return (0);
}

int list_flag(int argc, char **argv)
{
	char const base[] = "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";
	if ()
	return (0);
}

int	main (int argc, char **argv)
{
	if (list_flag(argc, argv) == 1)
		return (0);
	else if (list_files(argc, argv) == 1)
		return (0);
	return (0);
}
