/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 17:56:10 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/03 22:29:36 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** TODO:
*/

# include <stdio.h> //

# include "libft.h"

# define ARG_INIT ((t_arg){{0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}, 5, 0})

typedef struct	s_file
{
	char		*path;
	char		*name;
	int			ino;
	bool		is_fake;
	bool		is_dir;
	uint8_t		namelen;
	uint16_t	mode;
	uint16_t	nb_link;
	uint64_t	size;
	char		*gp_id;
	char		*user_id;
	int			ngp_id;
	int			nuser_id;
	int			atime;
	int			ctime;
	int			mtime;
}				t_file;

typedef struct	s_arg
{
	bool		arg[14];
	int			size;
	int			cursor;
}				t_arg;

/*
**Name: Print
**File: print_ls.c print_ls_ext.c print_ls_time.c
**Desc: print ls with options
*/

void			print_dirname(t_list *link);
void			print_total(t_list *list);
void			print_name(char *name);
void			print_ls(t_list *list, t_arg *arg_list);
void			print_nlink(uint16_t nlink);
void			print_time(int file_time);
int				nbrlen(uint64_t nbr);

/*
**Name: Parsing
**File: make_argv.c sort_argv.c make_list.c
**Desc: Parse files
*/

int				check_file(char *path, t_file *file);
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
