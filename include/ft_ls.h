/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 17:56:10 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/25 18:52:42 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** TODO:
*/

# include <stdio.h> //

# include "libft.h"

# define ARG_INIT ((t_arg){{0, 0, 0, 0, 0}, 5, 0})

typedef struct	s_file
{
	char		*path;
	char		*name;
	bool		is_fake;
	bool		is_dir;
	uint8_t		namelen;
	uint16_t	mode;
	uint16_t	nb_link;
	uint64_t	size;
	char		*gp_id;
	char		*user_id;
	int			atime;
	int			mtime;
}				t_file;

typedef struct	s_arg
{
	bool		arg[5];
	int			size;
	int			cursor;
}				t_arg;

/*
**Name: Print
**File: print.c
**Desc: print with options
*/

void			print_ls(t_list *list, t_arg *arg_list);

/*
**Name: Parsing
**File: make_argv.c sort_argv.c make_list.c
**Desc: Parse files
*/

int				recursive_list(t_list *list,t_arg *arg_list);
int				base_list(t_list *list, t_arg *arg_list);
int				sort_argv(t_list **list);
int				argv_to_list(char **argv, int argi, t_arg *arg_list);
int				sort_list(t_list **list, t_arg *arg_list);

/*
**Name: Get info
**File: get_stat.c
**Desc: Get information from stat
*/

int				get_stat(t_file *file);

#endif
