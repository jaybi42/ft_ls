/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/12 14:00:23 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/24 19:45:44 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_last(t_list **alst, t_list *new)
{
	if (*alst == NULL)
	{
		new->next = NULL;
		(*alst) = new;
	}
	else
	{
		while ((*alst)->next != NULL)
			*alst = (*alst)->next;
		new->next = NULL;
		(*alst)->next = new;
	}
}
