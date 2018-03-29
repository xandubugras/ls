/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:58:41 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/29 10:03:09 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

int		ft_ls(char **targets, t_input *input, int target_num, char *current_dir)
{
	t_file	*root;

	root = 0;
	if (target_num != 0)
		root = create_input_files(target_num, targets, current_dir);
	else
		root = create_all_files(current_dir, input);
	sort_list(&root, input);
	print_basic(root);
	//print_list(root, input);
	if (input->R)
		set_recursion(root);
	handle_recursion(root, input, current_dir);
	//print_basic(root);
		//if -R sets go_in_dir in all created folders
		//put targets in right order (lexicographical default)
		//list targets properly
		//while loop until go_in_dirs are over recursively calling*/
		//not add . folder if a is not
		//only show name if number of recursives is greater than 1
		//remove '/' of folder if input by user
	return (0);
}
	
t_file	*create_all_files(char *current_dir, t_input *input)
{
	DIR				*directory;
	struct dirent	*dir_info;
	t_file			*root;

	root = 0;
	if ((directory = opendir(current_dir)) == NULL)
		return ((t_file *)print_no_file_dir_err(current_dir));
	dir_info = readdir(directory);
	while (dir_info != NULL)
	{
		if (dir_info->d_name[0] != '.' || input->a)
			add_tlist_end(&root, dir_info->d_name, current_dir);
		dir_info = readdir(directory);
	}
	return (root);
}

t_file	*create_input_files(int target_num, char **targets, char *current_dir)
{
	t_file	*buf;
	t_file	*root;

	root = 0;
	while (target_num > 0)
	{
		remove_slash_end(targets[target_num - 1]);
		buf = add_tlist_end(&root, targets[target_num - 1], current_dir);
		if (buf->type == 'd' && NOT_CURR_PREV_DIR(buf))
			buf->go_in_dir = 1;
		target_num--;
	}
	return (root);
}

void	set_recursion(t_file *root)
{
	t_file *buf;

	buf = root;
	while (buf)
	{
		if (buf->type == 'd' && NOT_CURR_PREV_DIR(buf))
			buf->go_in_dir = 1;
		buf = buf->next;
	}
}

void	handle_recursion(t_file *root, t_input *input, char *current_dir)
{
	t_file *buf;

	buf = root;
	while (buf)
	{
		if (buf->go_in_dir)
		{
			buf->name = set_dir_path(current_dir, buf->name);
			ft_printf("%s:\n", buf->name);
			ft_ls(0, input, 0, buf->name);
			free(buf->name);
		}
		buf = buf->next;
	}
}
