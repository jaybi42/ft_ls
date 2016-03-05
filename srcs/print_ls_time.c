/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:59:44 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/05 18:15:45 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>

static char const g_month[10][3] = {
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
	"Dec",
};

static char const g_day[7][3] = {
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat",
	"Sun",
};

void			print_time(uint64_t file_time)
{
	time_t		get_time;
	time_t		t;
	int			i;
	int			year;

	year = 0;
	i = 0;
	get_time = time(&t);
	printf("\n%ld\n", t);
	printf("%llu\n", file_time);
	while (file_time > 31556926)
	{
		year++;
		file_time %= 31556926;
	}
	while (file_time > 2629743)
	{
		file_time %= 2629743;
		i++;
	}
	ft_putstr(g_month[i]);
	while (file_time > 2629743)
	{
		file_time %= 2629743;
		i++;
	}
	ft_putstr(g_month[i]);
	if ((ABS(file_time - t)) > 15778463)
	{
		ft_putstr(g_year[year]);
		return ;
	}
	//print hour
	//print minute

}
