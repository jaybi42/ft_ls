/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:12:17 by jguthert          #+#    #+#             */
/*   Updated: 2016/03/05 16:11:27 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <errno.h>

static void test_list(t_list **begin_list)
{
    t_list *drive;

    drive = *begin_list;
    while (drive != NULL)
    {
        if (S_ISDIR(((t_file *)drive->content)->mode) == 1)
            printf("\n%s:\n", ((t_file *)drive->content)->name);
        else
            printf("%s\n", ((t_file *)drive->content)->name);
        drive = drive->next;
    }
}

int			argv_to_list(char **argv, int argi, t_arg *arg_list)
{
	t_list	*tamp;
	t_list	*begin_list;
	t_file	file;

	if (get_stat(argv[argi--], &file) == 1)
		return (1);
	begin_list = ft_lstnew((void *)&file, sizeof(t_file));
	if (begin_list == NULL)
		return (1);
	while (argi > 0)
	{
		if (get_stat(argv[argi--], &file) == 1)
			return (1);
		tamp = ft_lstnew((void *)&file, sizeof(t_file));
		if (tamp == NULL)
			return (1);
		ft_lstadd(&begin_list, tamp);
	}
	if (sort_list(&begin_list, arg_list) == 1)
		return (1);
	if (arg_list->arg[5] == 0 && sort_argv(&begin_list) == 1)
		return (1);
	base_list(begin_list, arg_list);
	return (0);
}
