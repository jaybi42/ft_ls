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

static void		print_hm(char *str)
{
	//"Wed Jun 30 21:49:08 1993\n"
	while(ft_isdigit(*str) == 1)
	{
		ft_putchar(*str);
		str++;
	}
	ft_putchar(':');
	str++;
	while(ft_isdigit(*str) == 1)
	{
		ft_putchar(*str);
		str++;
	}
	ft_putchar(' ');
}

static void		print_year(char *str)
{
	while(*str != '\0')
		str++;
	str -= 4;
	while(ft_isdigit(str))
	{
		ft_putchar(*str);
		str++;
	}
	ft_putchar(' ');
}


static char		*print_md(char *str)
{
	while(ft_isascii(*str) == 1)
	{
		ft_putchar(*str);
		str++;
	}
	while(*str == ' ')
		str++;
	ft_putchar(' ');
	while(ft_isascii(*str) == 1)
	{
		ft_putchar(*str);
		str++;
	}
	ft_putchar(' ');
	while(ft_isdigit(*str) == 1)
	{
		ft_putchar(*str);
		str++;
	}
	ft_putchar(' ');
	while(*str == ' ')
		str++;
	return (str);
}

void			print_time(uint64_t file_time)
{
	time_t		get_time;
	time_t		t;
	char		*str;
	
	str = ctime(file_time);
	get_time = time(&t);
//"Wed Jun 30 21:49:08 1993\n"
	str = print_md(str);
	if (ABS((file_time - t)) > 15778463)
		print_year(str);
	else
		print_hm(str);
		
}
