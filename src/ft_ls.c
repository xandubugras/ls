/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:58:41 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/28 11:36:22 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

int		ft_ls(char **targets, t_input *input, int target_num, char *current_dir)
{
	t_file	*root;
	root = 0;
	if (target_num != 0)
	{
		while (target_num > 0)
		{
			add_tlist_end(&root, targets[target_num - 1], current_dir, 1);
			target_num--;
		}
		//create only mentioned targets;
		//if dir, go_in_dir becomes true and the dir itself is not added
	}
	else
	{
		root = create_all_files(current_dir);
		//create and set info of all files in current dir (only set the ones that start with . if -a)
	}
	sort_list(&root);
	//print_list(root);
	input = 0;
		//if -R sets go_in_dir in all created folders
		//put targets in right order (lexicographical default)
		//list targets properly
		//while loop until go_in_dirs are over recursively calling*/
	return (0);
}
	
t_file	*create_file(char *target_name, char *current_dir)
{
	DIR				*directory;
	struct dirent	*dir_info;
	t_file			*new_f;
	char			*short_name;

	short_name = target_name;
	if (target_name && ft_strchr(target_name, '/'))
	{
		current_dir = get_directory(target_name, current_dir);
		short_name = ft_get_last_char(target_name, '/') + 1;
	}
	if ((directory = opendir(current_dir)) == NULL)
		return ((t_file *)print_no_file_dir_err(current_dir));
	dir_info = readdir(directory);
	while (target_name && dir_info != NULL && ft_strcmp(dir_info->d_name, short_name))
		dir_info = readdir(directory);
	if (!target_name)
		target_name = ft_strdup(dir_info->d_name);
	if (dir_info != NULL)
	{
		new_f = new_file();
		set_file(target_name, new_f, current_dir);
		//print_struct(new_f);
	}
	else
		return ((t_file *)print_no_file_dir_err(target_name));
	return (new_f);
}

t_file	*create_all_files(char *current_dir)
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
		add_tlist_end(&root, dir_info->d_name, current_dir, 0);
		dir_info = readdir(directory);
	}
	return (root);
}


char	*get_directory(char *target_name, char *current_dir)
{
	char	*buf;
	char	*tmp;
	int		i;

	if (!target_name)
		return (current_dir);
	buf = ft_get_last_char(target_name, '/');
	i = 0;
	while (&(target_name[i]) != buf)
		i++;
	buf = ft_strndup(target_name, i + 1);
	tmp = buf;
	buf = ft_strjoin("/", buf);
	free(tmp);
	tmp = ft_strjoin(current_dir, buf);
	free(buf);
	return (tmp);
}
