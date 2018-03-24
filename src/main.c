/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:11:18 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/23 19:14:42 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		main(int argc, char **argv)
{
	//t_pointers *ptrs;
	t_grid **grid;
	int i;
	int j;

	if (argc != 2)
		return (1);
	grid = get_grid(argv[1]);
	convert_to_3d(grid);
	//ptrs = malloc(sizeof(t_pointers));
	//ptrs->mlx_ptr = mlx_init();
	//ptrs->win_ptr = mlx_new_window(ptrs->mlx_ptr, 800, 800, "mlx 42");
	j = 0;
	while (grid[j])
	{
		i = 0;
		while (!grid[j][i].last)
		{
			if (grid[j][i].z < 10 && grid[j][i].z > -10)
				printf(" %d ", grid[j][i].x);
			else
				printf("%d ", grid[j][i].x);
			i++;
		}
		j++;
		printf("\n");
	}
	//link_points(ptrs, grid);
	//mlx_key_hook(ptrs->win_ptr, on_key, ptrs);
	//mlx_mouse_hook(ptrs->win_ptr, on_click, ptrs);
	//mlx_loop(ptrs->mlx_ptr);
	//free(ptrs);
	j = 0;
	while (grid[j])
	{
		i = 0;
		while (grid[j][i].last)
		{
			free(&(grid[j][i]));
			i++;
		}
		j++;
	}
}


	/*x2 = 0;
	y2 = 250;
	while (x2 < 500)
	{
		draw_line(ptrs, x2, y2);
		x2++;
	}*/
