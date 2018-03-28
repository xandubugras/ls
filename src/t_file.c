/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 19:43:44 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/28 15:56:11 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

t_file	*new_file(void)
{
	t_file *new;

	if (!(new = malloc(sizeof(t_file))))
		ft_putstr_fd("ERROR CREATING FILE STRUCT\n", 2);
	new->name = 0;
	new->go_in_dir = 0;
	new->directory = 0;
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
	new->time_created = 0;
	new->time_modified = 0;
	new->time_last_opened = 0;
	new->next = NULL;
	new->no_show = 0;
	return (new);
}

int		set_file(char *target_name, t_file *new_file, char *current_dir)
{
	struct stat		file_info;
	struct passwd	*pwd;
	struct group	*grp;

	if (lstat(target_name, &file_info) != 0)
	{
		ft_printf("Error openning file\n");
		return (0);
	}
	new_file->name = target_name;
	new_file->directory = current_dir;
	new_file->time_created = file_info.st_birthtimespec.tv_sec;
	new_file->time_modified = file_info.st_mtimespec.tv_sec;
	new_file->time_last_opened = file_info.st_atimespec.tv_sec;
	new_file->file_size = file_info.st_size;
	new_file->num_links = file_info.st_nlink;
	new_file->blocks = file_info.st_blocks;
	pwd = getpwuid(file_info.st_uid);
	grp = getgrgid(file_info.st_gid);
	if(!pwd || !grp)
		ft_putstr_fd("puid not found", 2);
	new_file->owner_name = pwd->pw_name;
	new_file->group_name = grp->gr_name;;
	set_permission_and_type(new_file, file_info);
	return (1);
}

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
void	print_struct(t_file *new)
{
	ft_printf("\nname: %s\n", new->name);
	ft_printf("indir: %d\n", new->go_in_dir);
	ft_printf("dir: %s\n", new->directory);
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
	ft_printf("created: %s", new->time_created);
	ft_printf("modified: %s",new->time_modified);
	ft_printf("opened: %s", new->time_last_opened);
}
