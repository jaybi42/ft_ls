/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 14:10:01 by jguthert          #+#    #+#             */
/*   Updated: 2016/01/03 13:27:59 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char *str;

	if (!(str = (char*)malloc(size)))
		return (NULL);
	while (--size)
		str[size] = '\0';
	str[size] = '\0';
	return (str);
}
