/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:30:41 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/30 08:04:04 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H
# include "../libft/libft.h"
# define NOT_CUR_DIR(x) (ft_strcmp(x->name, ".") && ft_strcmp(x->name, ".."))

typedef struct	s_input
{
	int l;
	int ur;
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
	long long		time_modified;
	char			*name;
	int				blocks;
	struct s_file	*next;
}				t_file;
/*
**----------------input_info.c--------------------
*/
t_input			*new_input(void);

void			set_flags(char *arg, t_input *input);
/*
**----------------helpers.c------------------------
*/
void			*print_no_file_dir_err(char *file_name, char *free_str);

int				compare(t_input *input, t_file *f);

char			*set_dir_path(char *curr, char *target_name);

void			remove_slash_end(char *str);

char			*get_directory(char *target_name, char *curr);
/*
**----------------t_file.c------------------------
*/
t_file			*new_file(void);

t_file			*set_file(char *target_name, t_file *new_file, char *curr);

void			print_struct(t_file *new);

void			set_permission_and_type(t_file *new_file, struct stat f_info);

t_file			*create_file(char *target_name, char *curr);
/*
**----------------t_list.c------------------------
*/
t_file			*add_tlist_end(t_file **root, char *target_name, char *curr);

void			sort_list(t_file **root, t_input *input);

void			print_list(t_file *root, t_input *input);

void			print_details(t_file *f);

void			print_basic(t_file *f);

int				get_sum_blocks(t_file *root);
/*
**----------------ft_ls.c------------------------
*/

t_file			*create_all_files(char *curr, t_input *input);

t_file			*create_input_files(int target_num, char **targets, char *curr);

int				ft_ls(char **targets, t_input *inp, int target_num, char *curr);

void			set_recursion(t_file *root);

void			handle_recursion(t_file *root, t_input *input, char *curr);
#endif
