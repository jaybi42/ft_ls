/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:59:44 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/03 16:48:49 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>

void			print_time(int file_time)
{
	time_t		get_time;
	time_t		t;

	get_time = time(&t);
	//print month
	//print day
	if (file_time > get_time + 6 || file_time < get_time + 6)
	{
		//more than 6 mounth print the year
		return ;
	}
	//print hour
	//print minute

}
