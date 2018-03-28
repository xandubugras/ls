/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 09:10:54 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/28 15:56:03 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

t_file	*add_tlist_end(t_file **root, char *target_name, char *current_dir, char d)
{
	t_file *t;

	if (!(*root))
	{
		if ((*root = create_file(target_name, current_dir)) == NULL)
		{
			*root = 0;
			return (0);
		}
		if (d && ft_strcmp((*root)->name, ".") && ft_strcmp((*root)->name, "..") && (*root)->type == 'd')
			(*root)->go_in_dir = 1;
		return (*root);
	}
	t = *root;
	while (t->next != NULL)
		t = t->next;
	if ((t->next = create_file(target_name, current_dir)) == NULL)
		return (0);
	if (d && ft_strcmp(t->next->name, ".") && ft_strcmp(t->next->name, "..") && t->next->type == 'd')
		t->next->go_in_dir = 1;
	return (t->next);
}

void	sort_list(t_file **root, t_input *input)
{
	t_file	*t;
	t_file	*tmp;
	t_file	*prev;

	t = *root;
	prev = *root;
	while (t)
	{
		if (t->next && compare(input, t))//ft_numcmp(t->time_modified, t->next->time_modified) < 0)
		{
			tmp = t->next;
			t->next = tmp->next;
			tmp->next = t;
			if (t == *root)
				*root = tmp;
			else
				prev->next = tmp;
			t = *root;
			prev = *root;
		}
		else
		{
			prev = t != *root ? prev->next : prev;
			t = t->next;
		}
	}
}

void	print_list(t_file *root)
{
	while (root)
	{
		ft_printf("%s->", root->name);
		//print_struct(root);
		root = root->next;
	}
}
