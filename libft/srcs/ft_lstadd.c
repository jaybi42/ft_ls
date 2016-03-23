/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilberm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:22:33 by tsilberm          #+#    #+#             */
/*   Updated: 2015/11/30 22:24:15 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
	else
	{
		ft_putendl("HAHAHAH TU ME SEND DE LA MERDE");
		exit(-1);
	}

}
