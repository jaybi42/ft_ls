/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 17:56:10 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/23 21:55:54 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** TODO:
*/

# include <stdio.h> //

# include "libft.h"

# define FILE_INIT ((t_file){NULL, NULL, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL})
# define ARG_INIT ((t_arg){{0, 0, 0, 0, 0}, 5, 0})

typedef struct	s_file
{
	char		*path;
	char		*name;
	bool		is_fil;
	bool		is_dir;
	uint8_t		namelen;
	uint16_t	mode;
	uint16_t	nb_link;
	uint64_t	size;
	char		*gp_id;
	char		*user_id;
	char		*time_acces;
	char		*time_modif;
}				t_file;

typedef struct	s_arg
{
	bool		arg[5];
	int			size;
	int			cursor;
}				t_arg;

/*
**Name: Main
**File: main.c
**Desc: main
*/

/*
**Name: Parsing
**File: parsing.c
**Desc: Parse files
*/

t_list			*argv_to_list(char **argv, int max, int start, t_arg *arg_list);

/*
**Name: Parsing
**File: parsing.c
**Desc: Parse files
*/

void			sort_list(t_list **list, t_arg *arg_list);

/*
**Name: Parsing
**File: parsing.c
**Desc: Parse files
*/

//int				get_files(char *path);

/*
**Name: Get info
**File: get_stat.c
**Desc: Get information from stat
*/

int				get_stat(t_file *file);

#endif
