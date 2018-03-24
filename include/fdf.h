/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:11:40 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/23 18:33:01 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "../miniLibX/mlx.h"
# define FOCAL_DISTANCE 5
# define WIN_WIDTH 2000
# define WIN_HEIGHT 1500
# define START 200
# define SCALE 30

typedef	struct s_pointers
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_pointers;

typedef struct s_grid
{
	int				x;
	int				y;
	int				z;
	int				last;
	struct s_grid	*next;
}				t_grid;

void	draw_line(t_pointers *p, t_grid *grid, int x2, int y2);

t_grid	**get_grid(char *file_name);

int		on_click(int button, int x, int y, t_pointers *param);

int		on_key(int key, t_pointers *param);

int		get_grid_height(char *file_name);

int		get_grid_width_and_split(char ***splitted_line, int fd);

void	link_points(t_pointers *p, t_grid **grid);

int		find_max_height(t_grid **grid);

void	convert_to_3d(t_grid **grid);

t_grid	*construct_grid(int num_of_grids);

#endif
