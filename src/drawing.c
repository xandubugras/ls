/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:58:40 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/23 18:40:09 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#define SCALE 30
#define X2 p->x
#define Y2 p->y

void	draw_line(t_pointers *p, t_grid *grid, int x2, int y2)
{
	int i;
	int j;
	int err;
	int dx;
	int dy;

	i = grid->x;
	j = grid->y;
	if (i > x2)
		ft_swap(&i, &x2);
	if (j > y2)
		ft_swap(&j, &y2);
	dx = x2 - i;
	dy = y2 - j;
	err = dy - dx;
	ft_mod(&err);
	while (i <= (x2 - 1) || j <= (y2 - 1))
	{
		mlx_pixel_put(p->mlx_ptr, p->win_ptr, i, j, 0x000fff);
		if (err >= 0 && j != y2)
		{
			j++;
			err -= dx;
		}
		else
		{
			if (i != x2)
			{
				i++;
				err += dy;
			}
		}
	}
}

void	link_points(t_pointers *p, t_grid **grid)
{
	int i;
	int j;
	int x1;
	int y1;
	int max_height;

	j = 0;
	max_height = find_max_height(grid) + 1;
	while (grid[j])
	{
		i = 0;
		y1 = START + (j * SCALE);
		while (!grid[j][i].last)
		{
			x1 = START + (i * SCALE);
			if (!grid[j][i + 1].last)
				draw_line(p, &grid[j][i], x1, y1);
			if (grid[j + 1])
				draw_line(p, &grid[j][i], x1, y1);
			i++;
		}
		j++;
	}
}

int		find_max_height(t_grid **grid)
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

void	convert_to_3d(t_grid **grid)
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
			grid[j][i].x = ((FOCAL_DISTANCE * grid[j][i].x) / ((z_max + 1) - grid[j][i].z)) + WIN_WIDTH/2;
			grid[j][i].y = ((FOCAL_DISTANCE * grid[j][i].y) / ((z_max + 1) - grid[j][i].z)) + WIN_HEIGHT/2;
			i++;
		}
		j++;
	}
}



















