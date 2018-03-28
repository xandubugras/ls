/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:30:41 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/28 09:28:34 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H
# include "../libft/libft.h"
# define debug ft_printf("\nHERE\n");

typedef struct	s_input
{
	int l;
	int R;
	int a;
	int r;
	int t;
}				t_input;

typedef struct	s_file
{
	int				go_in_dir;
	char			type;
	int				o_read;
	int				o_write;
	int				o_execute;
	int				g_read;
	int				g_write;
	int				g_execute;
	int				x_read;
	int				x_write;
	int				x_execute;
	int				num_links;
	char			*owner_name;
	char			*group_name;
	long long		file_size;
	char			*time_created;
	char			*time_modified;
	char			*time_last_opened;
	char			*directory;
	char			*name;
	int				blocks;
	struct s_file	*next;
}				t_file;
/*
**----------------input_info.c--------------------
*/
t_input	*new_input(void);

void	set_flags(char *arg, t_input *input);
/*
**----------------helpers.c------------------------
*/
void	*print_no_file_dir_err(char *file_name);
/*
**----------------t_file.c------------------------
*/
t_file	*new_file(void);

int		set_file(char *target_name, t_file *new_file, char *current_dir);

void	print_struct(t_file *new);

void	set_permission_and_type(t_file *new_file, struct stat file_info);
/*
**----------------t_list.c------------------------
*/
t_file	*add_tlist_end(t_file **root, char *target_name, char *current_dir);
/*
**----------------ft_ls.c------------------------
*/
char	*get_directory(char *target_name, char *current_dir);

t_file	*create_file(char *target_name, char *current_dir);

int		ft_ls(char **targets, t_input *input, int target_num, char *current_dir);

#endif
