/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 19:43:44 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/30 08:14:43 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

/*
**Sets everything to 0;
*/

t_file	*new_file(void)
{
	t_file *new;

	if (!(new = malloc(sizeof(t_file))))
		ft_putstr_fd("ERROR CREATING FILE STRUCT\n", 2);
	new->name = 0;
	new->go_in_dir = 0;
	new->type = 0;
	new->o_read = 0;
	new->o_write = 0;
	new->o_execute = 0;
	new->g_read = 0;
	new->g_write = 0;
	new->g_execute = 0;
	new->x_read = 0;
	new->x_write = 0;
	new->x_execute = 0;
	new->num_links = 0;
	new->blocks = 0;
	new->owner_name = 0;
	new->group_name = 0;
	new->file_size = 0;
	new->time_modified = 0;
	new->next = NULL;
	return (new);
}

/*
**sets the information for the files
*/

t_file	*set_file(char *target_name, t_file *new_file, char *current_dir)
{
	struct stat		file_info;
	struct passwd	*pwd;
	struct group	*grp;
	char			*full_path;

	new_file->name = ft_strdup(target_name);
	if (ft_strcmp(current_dir, "."))
		full_path = set_dir_path(current_dir, target_name);
	else
		full_path = target_name;
	if (lstat(full_path, &file_info) != 0)
		return (0);
	if (ft_strcmp(current_dir, "."))
		free(full_path);
	pwd = getpwuid(file_info.st_uid);
	grp = getgrgid(file_info.st_gid);
	new_file->owner_name = ft_strdup(pwd->pw_name);
	new_file->group_name = ft_strdup(grp->gr_name);
	new_file->time_modified = file_info.st_mtimespec.tv_sec;
	new_file->file_size = file_info.st_size;
	new_file->num_links = file_info.st_nlink;
	new_file->blocks = file_info.st_blocks;
	set_permission_and_type(new_file, file_info);
	return (new_file);
}

/*
**permissions and type
*/

void	set_permission_and_type(t_file *new_file, struct stat file_info)
{
	if (file_info.st_mode & S_IFREG)
		new_file->type = '-';
	else if (file_info.st_mode & S_IFDIR)
		new_file->type = 'd';
	else if (file_info.st_mode & S_IFIFO)
		new_file->type = 'p';
	else if (file_info.st_mode & S_IFCHR)
		new_file->type = 'c';
	else if (file_info.st_mode & S_IFBLK)
		new_file->type = 'b';
	else if (file_info.st_mode & S_IFLNK)
		new_file->type = 'l';
	else if (file_info.st_mode & S_IFSOCK)
		new_file->type = 's';
	else
		new_file->type = 'o';
		new_file->o_read = file_info.st_mode & S_IRUSR ? 'r' : '-';
		new_file->o_write = file_info.st_mode & S_IWUSR ? 'w' : '-';
		new_file->o_execute = file_info.st_mode & S_IXUSR ? 'x' : '-';
		new_file->g_read = file_info.st_mode & S_IRGRP ? 'r' : '-';
		new_file->g_write = file_info.st_mode & S_IWGRP ? 'w' : '-';
		new_file->g_execute = file_info.st_mode & S_IXGRP ? 'x' : '-';
		new_file->x_read = file_info.st_mode & S_IROTH ? 'r' : '-';
		new_file->x_write = file_info.st_mode & S_IWOTH ? 'w' : '-';
		new_file->x_execute = file_info.st_mode & S_IXOTH ? 'x' : '-';
}

/*
**gets the information and reates the object accordingly
*/

t_file	*create_file(char *target_name, char *current_dir)
{
	DIR				*directory;
	struct dirent	*dir_info;
	t_file			*new_f;
	char			*short_name;

	short_name = target_name;
	current_dir = ft_strdup(current_dir);
	if (target_name && ft_strchr(target_name, '/'))
	{
		current_dir = get_directory(target_name, current_dir);
		short_name = ft_get_last_char(target_name, '/') + 1;
	}
	if ((directory = opendir(current_dir)) == NULL)
		return ((t_file *)print_no_file_dir_err(current_dir, current_dir));
	dir_info = readdir(directory);
	while (target_name && dir_info && ft_strcmp(dir_info->d_name, short_name))
		dir_info = readdir(directory);
	closedir(directory);
	target_name = target_name == 0 && dir_info ? dir_info->d_name : target_name;
	if (!dir_info)
		return ((t_file *)print_no_file_dir_err(target_name, current_dir));
	else
		new_f = set_file(target_name, new_file(), current_dir);
	free(current_dir);
	return (new_f);
}

/*
**Debug helping function that prints the struct
*/

void	print_struct(t_file *new)
{
	ft_printf("\nname: %s\n", new->name);
	ft_printf("indir: %d\n", new->go_in_dir);
	ft_printf("type: %c\n", new->type);
	ft_printf("o_read: %c\n", new->o_read);
	ft_printf("owrite: %c\n", new->o_write);
	ft_printf("oexecute: %c\n", new->o_execute);
	ft_printf("gread: %c\n", new->g_read);
	ft_printf("gwrite: %c\n", new->g_write);
	ft_printf("gexecute: %c\n", new->g_execute);
	ft_printf("xread: %c\n", new->x_read);
	ft_printf("xwrite: %c\n", new->x_write);
	ft_printf("xexecute: %c\n", new->x_execute);
	ft_printf("numlinks: %d\n", new->num_links);
	ft_printf("blocks: %d\n", new->blocks);
	ft_printf("ownername: %s\n", new->owner_name);
	ft_printf("ownergroup: %s\n", new->group_name);
	ft_printf("size: %lld\n", new->file_size);
	ft_printf("modified: %lld", new->time_modified);
}
