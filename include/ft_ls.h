/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 17:56:10 by jguthert          #+#    #+#             */
/*   Updated: 2016/04/12 17:21:35 by jguthert         ###   ########.fr       */
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

# define ARG_INIT ((t_arg){{0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}})

typedef struct	s_maxlen
{
	int			gp;
	int			user;
	int			ino;
	int			size;
	int			nb_link;
	int			major;
	int			minor;
}				t_maxlen;

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
	char		*lnk_path;
	int			error;
	uint16_t	mode;
	uint16_t	nb_link;
	uint64_t	size;
	uint64_t	blocks;
	uint64_t	dev;
	int			ino;
	int			major;
	int			minor;
	time_t		time;
	uint64_t	nano;
	t_id		id;
}				t_file;

typedef struct	s_arg
{
	bool		arg[14];
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

int				add_list(char *path, t_arg *arg_list, t_list **new_list);
int				base_list(t_list *list, t_arg *arg_list, bool alon, bool first);
int				argv_to_list(char **argv, int argi, t_arg *arg_list);
int				sort_list(t_list **list, t_arg *arg_list);
void			free_list(void *content, size_t size);

/*
**Name: Get info
**File: get_stat.c
**Desc: Get information from stat
*/

int				get_stat(char *path, t_file *file, t_arg *arg_list);

#endif
