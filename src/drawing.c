/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:58:40 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/24 20:46:16 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	swap_if(int *i, int *j, int *x2, int *y2)
{
	if (*i > *x2)
		ft_swap(i, x2);
	if (*j > *y2)
		ft_swap(j, y2);
	return (*x2 - *i);
}

void		draw_line(t_pointers *p, t_grid *grid, int x2, int y2)
{
	int i;
	int j;
	int err;
	int dx;
	int dy;

	i = grid->x;
	j = grid->y;
	dx = swap_if(&i, &j, &x2, &y2);
	dy = y2 - j;
	err = ft_return_mod(dy - dx);
	while (i <= (x2 - 1) || j <= (y2 - 1))
	{
		mlx_pixel_put(p->mlx_ptr, p->win_ptr, i, j, 0x000fff);
		if (err >= 0 && j != y2)
		{
			j++;
			err -= dx;
		}
		else if (i != x2)
		{
			i++;
			err += dy;
		}
	}
}

void		link_points(t_pointers *p, t_grid **grid)
{
	int i;
	int j;
	int max_height;

	j = 0;
	max_height = find_max_height(grid) + 1;
	while (grid[j])
	{
		i = 0;
		while (!grid[j][i].last)
		{
			if (!grid[j][i + 1].last)
				draw_line(p, &grid[j][i], grid[j][i + 1].x, grid[j][i + 1].y);
			if (grid[j + 1])
				draw_line(p, &grid[j][i], grid[j + 1][i].x, grid[j + 1][i].y);
			i++;
		}
		j++;
	}
}

int			find_max_height(t_grid **grid)
{
	int i;
	int j;
	int max;

	j = 0;
	max = 0;
	while (grid[j])
	{
		i = 0;
		while (!grid[j][i].last)
		{
			if (grid[j][i].z > max)
				max = grid[j][i].z;
			i++;
		}
		j++;
	}
	return (max);
}

void		convert_to_3d(t_grid **grid)
{
	int i;
	int j;
	int z_max;

	j = 0;
	z_max = find_max_height(grid);
	while (grid[j])
	{
		i = 0;
		while (!grid[j][i].last)
		{
			grid[j][i].x = ((FOCAL_DISTANCE * grid[j][i].x) /
					((z_max + 5) - grid[j][i].z)) + WIN_WIDTH / 4;
			grid[j][i].y = ((FOCAL_DISTANCE * grid[j][i].y) /
					((z_max + 5) - grid[j][i].z)) + WIN_HEIGHT / 4;
			i++;
		}
		j++;
	}
}
