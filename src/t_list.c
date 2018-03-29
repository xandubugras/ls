/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 09:10:54 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/29 15:21:26 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

/*
**If list is empty, adds the first, else, adds it to the end
*/
t_file	*add_tlist_end(t_file **root, char *target_name, char *current_dir)
{
	t_file *t;

	if (!(*root))
	{
		if ((*root = create_file(target_name, current_dir)) == NULL)
			return (0);
		return (*root);
	}
	t = *root;
	while (t->next != NULL)
		t = t->next;
	if ((t->next = create_file(target_name, current_dir)) == NULL)
		return (0);
	return (t->next);
}
/*
**uses bubble sort to sort the linked list
*/

void	sort_list(t_file **root, t_input *input)
{
	t_file	*t;
	t_file	*tmp;
	t_file	*prev;

	t = *root;
	prev = *root;
	while (t)
		if (t->next && compare(input, t))
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
/*
**prints the list accordingly
*/

void	print_list(t_file *root, t_input *input)
{
	t_file *buf;
	int		i;

	i = 0;
	buf = root;
	if (input->l && !buf->go_in_dir)
		ft_printf("total %d\n", get_sum_blocks(buf));
	while (buf)
	{
		if (!buf->go_in_dir)
		{
			i = 1;
			if (input->l)
				print_details(buf);
			else
				ft_printf("%s\t", buf->name);
		}
		buf = buf->next;
	}
	if (!input->l && i)
		ft_putchar('\n');
}
/*
**
*/

void	print_basic(t_file *root)
{
	t_file *buf;

	buf = root;
	while (buf)
	{
		ft_printf("%s->\n", buf->name);
		buf = buf->next;
	}
}
/*
**prints -l details that are saved to file
*/

void	print_details(t_file *f)
{
	char *time;

	ft_printf("%c%c%c%c%c%c%c%c%c%c  ",f->type, f->o_read, f->o_write,
			f->o_execute, f->g_read, f->g_write, f->g_execute, f->x_read, f->x_write, f->x_execute);
	ft_printf("%d ", f->num_links);
	ft_printf("%s  ", f->owner_name);
	ft_printf("%s", f->group_name);
	ft_printf("%7d ", f->file_size);
	time = ctime((time_t *)&(f->time_modified));
	time = ft_strndup(time, ft_strlen(time) - 1);
	time[16] = '\0';
	ft_printf("%s ", &time[4]);
	free(time);
	ft_printf("%s", f->name);
	ft_printf("\n");
}
/*
**sums num of blocks for -l
*/

int		get_sum_blocks(t_file *root)
{
	int sum;

	sum = 0;
	while (root)
	{
		sum += root->blocks;
		root = root->next;
	}
	return (sum);
}
