/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 09:10:54 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/28 21:30:33 by adubugra         ###   ########.fr       */
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
			debug
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

void	print_list(t_file *root, t_input *input)
{
	if (input->l)
		ft_printf("total %d\n", get_sum_blocks(root, input));
	while (root)
	{
		if (!root->go_in_dir)
		{
			if (input->a)
			{
				if (input->l)
					print_details(root);
				else
					ft_printf("%s\t", root->name);
			}
			else if (root->name[0] != '.')
			{
				if (input->l)
					print_details(root);
				else
					ft_printf("%s\t", root->name);
			}
		}
		root = root->next;
	}
	ft_printf("\n");
}

void	print_basic(t_file *root)
{
	while (root)
	{
		ft_printf("%s->", root->name);
		root = root->next;
	}
}

void	print_details(t_file *f)
{
	char *time;

	ft_printf("%c%c%c%c%c%c%c%c%c%c  ",f->type, f->o_read, f->o_write,
			f->o_execute, f->g_read, f->g_write, f->g_execute, f->x_read, f->x_write, f->x_execute);
	ft_printf("%d ", f->num_links);
	ft_printf("%s  ", f->owner_name);
	ft_printf("%s", f->group_name);
	ft_printf("%8d ", f->file_size);
	time = ctime((time_t *)&(f->time_modified));
	time = ft_strndup(time, ft_strlen(time) - 1);
	ft_printf("%s ", time);
	free(time);
	ft_printf("%s", f->name);
	ft_printf("\n");
}

int		get_sum_blocks(t_file *root, t_input *input)
{
	int sum;

	sum = 0;
	while (root)
	{
		if (input->a)
			sum += root->blocks;
		else if (root->name[0] != '.')
			sum += root->blocks;
		root = root->next;
	}
	return (sum);
}
