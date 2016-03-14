/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 17:56:10 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/14 17:11:36 by jguthert         ###   ########.fr       */
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

typedef struct	s_maxlen
{
	int			gp;
	int			user;
	int			ino;
	int			size;
	int			nb_link;
}				t_maxlen;

typedef struct	s_time
{
	time_t		atime;
	uint64_t	anano;
	time_t		ctime;
	uint64_t	cnano;
	time_t		mtime;
	uint64_t	mnano;
}				t_time;

typedef struct	s_id
{
	char		*gp;
	int			gp_len;
	char		*user;
	int			user_len;
	int			ngp;
	int			nuser;
}				t_id;

typedef struct	s_file
{
	char		*path;
	char		*name;
	int			error;
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
**File: print_ls.c print_ls_ext.c print_ls_time.c print_ls_error.c
**Desc: print ls with options
*/

void			print_ls(t_list *list, t_arg *arg_list);
void			print_ls_ext(t_file *file, t_arg *arg_list, t_maxlen *maxlen);
void			print_time(time_t file_time);
void			print_error(char *name, int error);

/*
**Name: Parsing
**File: make_argv.c sort_argv.c make_list.c
**Desc: Parse files
*/

int				base_list(t_list *list, t_arg *arg_list);
int				sort_argv(t_list **list);
int				argv_to_list(char **argv, int argi, t_arg *arg_list);
int				sort_list(t_list **list, t_arg *arg_list);
void			free_list(void *content, size_t size);

/*
**Name: Get info
**File: get_stat.c
**Desc: Get information from stat
*/

int				get_stat(char *path, t_file *file);

#endif
