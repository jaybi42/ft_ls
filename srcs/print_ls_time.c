/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:59:44 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/10 18:44:08 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>

static char const *g_month[12] = {
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aou",
	"Sep",
	"Oct",
	"Nov",
	"Dec"
};

void			print_time(uint64_t file_time)
{
	time_t		get_time;
	time_t		t;
	int			year;
	uint64_t	ret;

	year = 1970;
	get_time = time(&t);
	year = year + file_time / 31556926;
	file_time %= 31556926;
	ft_putstr(g_month[file_time / 2629743]);
	ret = (ABS(file_time - t));
	ft_putchar(' ');
	file_time %= 2629743;
	ft_putnbr(file_time / 86400);
	file_time / 86400 < 10 ? ft_putchar(' ') : ft_putstr("  ");
	if (ret > 15778463)
		ft_putnbr(year);
	else
	{
		file_time %= 86400;
		ft_putnbr(file_time / 3600);
		file_time %= 3600;
		ft_putchar(':');
		ft_putnbr(file_time / 60);
	}
	ft_putchar(' ');
}
