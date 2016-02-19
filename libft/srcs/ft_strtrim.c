/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:27:22 by jguthert          #+#    #+#             */
/*   Updated: 2016/01/03 13:32:07 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	int		i;
	char	*str;

	while (*s == '\t' || *s == ' ' || *s == '\n')
		s++;
	if (!*s)
		return ("");
	i = ft_strlen(s) - 1;
	while (s[i] == '\t' || s[i] == ' ' || s[i] == '\n')
		i--;
	i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	while (--i >= 0)
		str[i] = s[i];
	return (str);
}
