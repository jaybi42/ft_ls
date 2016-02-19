/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 17:56:10 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/19 20:28:02 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** TODO:
*/

# include <stdio.h> //

# include "libft.h"

# define FILE_INIT ((t_file){NULL, 0, 0, 0, NULL, NULL, NULL, NULL})

typedef struct	s_file
{
	char		*path;
	uint16_t	mode;
	uint16_t	nb_link;
	uint64_t	size;
	char		*gp_id;
	char		*user_id;
	char		*time_acces;
	char		*time_modif;
}				t_file;

/*
**Name: Main
**File: main.c
**Desc: main
*/

/*
**Name: Get info
**File: get_stat.c
**Desc: Get information from stat
*/

int				get_stat(t_file *file);

#endif
