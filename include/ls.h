/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:30:41 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/29 10:10:18 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H
# include "../libft/libft.h"
# define debug ft_printf("\nHERE\n");
# define NOT_CURR_PREV_DIR(added) (ft_strcmp(added->name, ".") && ft_strcmp(added->name, ".."))

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
	char			go_in_dir;
	char			type;
	char			o_read;
	char			o_write;
	char			o_execute;
	char			g_read;
	char			g_write;
	char			g_execute;
	char			x_read;
	char			x_write;
	char			x_execute;
	char			*owner_name;
	char			*group_name;
	int				num_links;
	long long		file_size;
	long long		time_created;
	long long		time_modified;
	long long		time_last_opened;
	char			*directory;
	char			*name;
	int				blocks;
	int				no_show;
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

int		compare(t_input *input, t_file *f);

char	*set_dir_path(char *current_dir, char *target_name);

void	remove_slash_end(char *str);

char	*get_directory(char *target_name, char *current_dir);
/*
**----------------t_file.c------------------------
*/
t_file	*new_file(void);

t_file	*set_file(char *target_name, t_file *new_file, char *current_dir);

void	print_struct(t_file *new);

void	set_permission_and_type(t_file *new_file, struct stat file_info);

t_file	*create_file(char *target_name, char *current_dir);
/*
**----------------t_list.c------------------------
*/
t_file	*add_tlist_end(t_file **root, char *target_name, char *current_dir);

void	sort_list(t_file **root, t_input *input);

void	print_list(t_file *root, t_input *input);

void	print_details(t_file *f);

void	print_basic(t_file *f);

int		get_sum_blocks(t_file *root, t_input *input);
/*
**----------------ft_ls.c------------------------
*/

t_file	*create_all_files(char *current_dir, t_input *input);

t_file	*create_input_files(int target_num, char **targets,char *current_dir);

int		ft_ls(char **targets, t_input *input, int target_num, char *current_dir);

void	set_recursion(t_file *root);

void	handle_recursion(t_file *root, t_input *input, char *current_dir);
#endif
