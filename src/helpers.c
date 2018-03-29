/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:32:32 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/28 21:05:57 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

void	*print_no_file_dir_err(char *file_name)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (0);
}

int		compare(t_input *input, t_file *f)
{
	int i;

	i = input->t ? ft_numcmp(f->time_modified, f->next->time_modified) < 0:
		ft_strcmp(f->name, f->next->name) > 0;
	if (input->r)
	{
		if (!input->t)
			i = !i;
		else
			i = ft_numcmp(f->time_modified, f->next->time_modified) > 0;
	}
	return (i);
}

char	*set_dir_path(char *current_dir, char *target_name)
{
	char	*new;
	int		dir_len;

	if (ft_strcmp(current_dir, "."))
	{
		dir_len = ft_strlen(current_dir) - 1;
		new = ft_strjoin(current_dir, target_name);
		if (new[dir_len] != '/')
			ft_strinsert(&new, "/", dir_len + 1);
		return (new);
	}
	return (target_name);
}
