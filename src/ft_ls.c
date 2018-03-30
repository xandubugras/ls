/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:58:41 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/29 21:00:46 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

/*
**ft_ls is the main controlling functions. it first creates a list of
**all the files to be displayed, with their respective info
**after that it sorts the list accordingly, prints it and then
**handles the recursion.
*/

int		ft_ls(char **targets, t_input *input, int target_num, char *current_dir)
{
	t_file	*root;
	t_file	*buf;

	root = 0;
	if (target_num != 0)
		root = create_input_files(target_num, targets, current_dir);
	else
		root = create_all_files(current_dir, input);
	sort_list(&root, input);
	print_list(root, input);
	if (input->ur)
		set_recursion(root);
	handle_recursion(root, input, current_dir);
	buf = root;
	while (buf)
	{
		root = root->next;
		free(buf->name);
		free(buf->owner_name);
		free(buf->group_name);
		free(buf);
		buf = root;
	}
	return (0);
}

/*
**In case the user doesn't input a directory, it lists all
**objects in the current directory
*/

t_file	*create_all_files(char *current_dir, t_input *input)
{
	DIR				*directory;
	struct dirent	*dir_info;
	t_file			*root;

	if ((directory = opendir(current_dir)) == NULL)
		return ((t_file *)print_no_file_dir_err(current_dir));
	dir_info = readdir(directory);
	root = 0;
	while (dir_info != NULL)
	{
		if (dir_info->d_name[0] != '.' || input->a)
			add_tlist_end(&root, dir_info->d_name, current_dir);
		dir_info = readdir(directory);
	}
	closedir(directory);
	return (root);
}

/*
**In case user does insert targets, this function only adds those to list
*/

t_file	*create_input_files(int target_num, char **targets, char *current_dir)
{
	t_file	*buf;
	t_file	*root;

	root = 0;
	while (target_num > 0)
	{
		remove_slash_end(targets[target_num - 1]);
		buf = add_tlist_end(&root, targets[target_num - 1], current_dir);
		if (buf)
		{
			if (buf->type == 'd')
				buf->go_in_dir = 1;
		}
		else
			return (0);
		target_num--;
	}
	return (root);
}

/*
**After sortinf, if the -R is on, this function sets all dir in
**the list to be recursively called
*/

void	set_recursion(t_file *root)
{
	t_file *buf;

	buf = root;
	while (buf)
	{
		if (buf->type == 'd' && NOT_CUR_DIR(buf))
			buf->go_in_dir = 1;
		buf = buf->next;
	}
}

/*
**Actually calls all the directories
*/

void	handle_recursion(t_file *root, t_input *input, char *current_dir)
{
	t_file	*buf;
	char	*new_path;

	buf = root;
	while (buf)
	{
		if (buf->go_in_dir)
		{
			new_path = set_dir_path(current_dir, buf->name);
			ft_printf("%s:\n", new_path);
			ft_ls(0, input, 0, new_path);
			ft_printf("\n");
			free(new_path);
		}
		buf = buf->next;
	}
}
