/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 17:56:10 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/05 18:12:51 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** TODO:
*/

# include <stdio.h> //

# include "libft.h"
#include <sys/stat.h>

# define ARG_INIT ((t_arg){{0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}, 5, 0})

typedef struct	s_time
{
	uint64_t	atime;
	uint64_t	anano;
	uint64_t	ctime;
	uint64_t	cnano;
	uint64_t	mtime;
	uint64_t	mnano;
}				t_time;

typedef struct	s_id
{
	char		*gp_id;
	char		*user_id;
	int			ngp_id;
	int			nuser_id;
}				t_id;

typedef struct	s_file
{
	char		*path;
	char		*name;
	bool		is_fake;
	uint8_t		namelen;
	uint16_t	mode;
	uint16_t	nb_link;
	uint64_t	size;
	uint64_t	dev;
	int			ino;
	int			major;
	int			minor;
	t_id		id;
	t_time		time;
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
void			print_name(char *name, bool is_lnk);
void			print_ls(t_list *list, t_arg *arg_list);
void			print_nlink(uint16_t nlink);
void			print_time(uint64_t file_time);
int				nbrlen(uint64_t nbr);

/*
**Name: Parsing
**File: make_argv.c sort_argv.c make_list.c
**Desc: Parse files
*/

int				base_list(t_list *list, t_arg *arg_list);
int				sort_argv(t_list **list);
int				argv_to_list(char **argv, int argi, t_arg *arg_list);
int				sort_list(t_list **list, t_arg *arg_list);

/*
**Name: Get info
**File: get_stat.c
**Desc: Get information from stat
*/

int				get_stat(char *path, t_file *file);

#endif
