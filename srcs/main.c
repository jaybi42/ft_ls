/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 18:00:58 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/17 14:22:13 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	is_in(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int list_flag(int argc, char **argv)
{
	char const base[] = "Ralrt";
	char		*tmp;
	int			i;

	i = 1;
	while (i < argc)
	{
		tmp = argv[i];
		if (*tmp != '-')
			return (0);
		tmp++;
		while (*tmp)
		{
			printf("option %c\n", *tmp);
			if (is_in(*tmp, base) == 1)
			{
				printf("stack %c\n", *tmp);
				//tab[j] = 1;
			}
			else
			{
				ft_putstr("ls: illegal option -- ");
				ft_putchar_fd(*tmp, 2);
				ft_putchar('\n');
				return (1);
			}
			tmp++;
		}
		i++;
	}
	return (0);
}

int list_files(int argc, char **argv)
{
	printf("GOOD\n");
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
